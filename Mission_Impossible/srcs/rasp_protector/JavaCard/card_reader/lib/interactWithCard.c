#include "headers/interactWithCard.h"

/*
APDU_select_applet permet de transmettre a la carte la requete APDU qui
permet la selection de l'applet utilise pour ce projet

input :
	card_reader_t ** : structure qui contient la connection au lecteur de carte et a la carte
	BYTE *           : chaine de BYTE qui contiendra le retour de la carte
	int *            : nombre de BYTE recu par la carte

output:
	same as send_APDU_request fonction
*/
int APDU_select_applet(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len) {
	BYTE APDU_cmd_select_applet[] = {
		0x00, 0xA4, 0x04, 0x00, 0x0b, 0x01, 0x02,
		0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x00, 0x01, 0x7F
	}; // commande APDU pour selctionner l'applet dans la carte

	return send_APDU_request(
		&(*cardReader),
		APDU_cmd_select_applet,
		(DWORD) 17,
		APDU_dst,
		&(*APDU_len)
	);
}

/*
APDU_valid_pin permet de faire valider un code pin a la carte via la structure card_reader_t
qui dois etre connecte a un lecteur de carte et une carte.

input :
	card_reader_t ** : structure qui contient la connection au lecteur de carte et a la carte
	BYTE *           : chaine de BYTE qui contiendra le retour de la carte
	int *            : nombre de BYTE recu par la carte
	char *           : code a transmetre a la carte (dois faire 4 char)

output:
	same as send_APDU_request fonction
*/
int APDU_valid_pin(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len, char *code) {
	BYTE APDU_cmd_validate_pin[10] = {
		0x80, 0x22, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F
//      CLA   INS   P1    P2    LC    -------- CODE --------  LE
	}; // commande APDU pour valider un code pin
	int i;

	for (i=0; i < 4; i++)
		APDU_cmd_validate_pin[i + 5] = (BYTE)code[i];

	return send_APDU_request(
		&(*cardReader),
		APDU_cmd_validate_pin,
		(DWORD) 10,
		APDU_dst,
		&(*APDU_len)
	);
}

/*
APDU_get_id permet de recuperer l'id contenue dans la carte une fois que le
code PIN a ete renseigne.

input :
	card_reader_t ** : structure qui contient la connection au lecteur de carte et a la carte
	BYTE *           : chaine de BYTE qui contiendra le retour de la carte
	int *            : nombre de BYTE recu par la carte

output:
	same as send_APDU_request fonction
*/
int APDU_get_id(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len) {
	int returnValue;
	BYTE APDU_cmd_get_id[] = {
		0x80, 0x23, 0x00, 0x00, 0x7F
//      CLA   INS   P1    P2    LE
	};

	return send_APDU_request(
		&(*cardReader),
		APDU_cmd_get_id,
		(DWORD) 5,
		APDU_dst,
		&(*APDU_len)
	);
}

/*
send_APDU_request permet de transmettre un requete APDU a une carte. Pour cela il faut utiliser
la structure card_reader_t qui dois etre connecte a une carte avec les commande find_card_readers et
connect_to_card sans erreur.

input :
	card_reader_t ** : structure qui contient la connection au lecteur de carte et a la carte
	BYTE *           : chaine de BYTE qui contient la requete APDU a envoyer
	DWORD            : taille de la requete APDU
	BYTE *           : chaine de BYTE qui contiendra le retour de la carte
	int *            : nombre de BYTE recu par la carte

output:
	_SUCCESS_                   : si aucunne arreur n'est arrive durant la communication
	SCARD_E_INSUFFICIENT_BUFFER : si la taille du buffer est insufisant
	SCARD_E_INVALID_HANDLE      : si le handle est invalide
	SCARD_E_INVALID_PARAMETER   : si les parametre sont incorrect
	SCARD_E_INVALID_VALUE       : si les valeurs ne sont pas correct
	SCARD_E_NO_SERVICE          : si il n'y a pas de service
	SCARD_E_NOT_TRANSACTED      : si la requete APDU n'est pas arrive a son terme
	SCARD_E_PROTO_MISMATCH      : si le protocole est incorect
	SCARD_E_READER_UNAVAILABLE  : si le lecteur est invalide
	SCARD_F_COMM_ERROR          : en cas d'erreur interne de la communication
	SCARD_W_RESET_CARD          : si la carte a ete reset par une autres application
	SCARD_W_REMOVED_CARD        : si la carte a ete supprimer par le lecteur
*/
int send_APDU_request(card_reader_t **cardReader, BYTE *APDU_src, DWORD APDU_src_len, BYTE *APDU_dst, int *APDU_dst_len) {
	BYTE pbRecvBuffer[258];
	DWORD dwRecvLength;
	LONG rv;
	int i = -1;

	dwRecvLength = sizeof(pbRecvBuffer);
	rv = SCardTransmit(
		(*cardReader)->hCard,
		&( (*cardReader)->pioSendPci ),
		APDU_src,
		APDU_src_len,
		NULL,
		pbRecvBuffer,
		&dwRecvLength
	);

	if (rv != SCARD_S_SUCCESS) { free((*cardReader)); *cardReader = NULL; return rv; }

	while (++i < dwRecvLength)
		APDU_dst[i] = pbRecvBuffer[i];
	APDU_dst[i] = 0x00;

	*APDU_dst_len = dwRecvLength;
	return _SUCCESS_;
}

/*
made_full_communication_with_card permet d'etablir la procedure pour communiquer
avec la carte et ainsi recupere l'id de la carte si tous se passe bien

input :
	card_reader_t ** : structure qui contient la connection au lecteur de carte et a la carte
	char *           : code renseigne par l'utilisateur
	int *            : id retourne par la carte

output:
	_SUCCESS_                    : si tous c'est bien passe
	_ERROR_DURING_COMMUNICATION_ : si erreur durant la communication avec la carte
	_ERROR_CANT_SELECT_APPLET_   : si l'applet n'a pas pue etre charge
	_ERROR_BAD_PIN_              : si mauvais PIN
	_ERROR_DURING_GET_ID_        : si erreur durant la recuperation de l'id
*/
int made_full_communication_with_card(card_reader_t **cardReader, char *code, int *id) {
	int returnValue = 0;
	BYTE response_APDU[50];
	int response_APDU_len;

	*id = 0;

	/* On choisie l'applet sur la carte */
	returnValue = APDU_select_applet(&(*cardReader), response_APDU, &response_APDU_len);
	if (returnValue != _SUCCESS_) return _ERROR_DURING_COMMUNICATION_;
	if (response_APDU[response_APDU_len-2] != 0x90 || response_APDU[response_APDU_len-1] != 0x00)
		return _ERROR_CANT_SELECT_APPLET_; // si la reponse n'est pas 0x90 00

	/* demande de validation du code PIN */
	returnValue = APDU_valid_pin(&(*cardReader), response_APDU, &response_APDU_len, code);
	if (returnValue != _SUCCESS_) return _ERROR_DURING_COMMUNICATION_;
	if (response_APDU[response_APDU_len-2] != 0x90 || response_APDU[response_APDU_len-1] != 0x00)
		return _ERROR_BAD_PIN_; // si la reponse n'est pas 0x90 00

	/* recuperation de l'id contenue dans la carte */
	returnValue = APDU_get_id(&(*cardReader), response_APDU, &response_APDU_len);
	if (returnValue != _SUCCESS_) return _ERROR_DURING_COMMUNICATION_;
	if (response_APDU[response_APDU_len-2] != 0x90 || response_APDU[response_APDU_len-1] != 0x00)
		return _ERROR_DURING_GET_ID_; // si la reponse n'est pas 0x90 00

	*id = (int)response_APDU[0];
	return _SUCCESS_;
}