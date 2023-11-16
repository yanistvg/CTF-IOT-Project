#include "headers/interactWithReader.h"

/*
find_card_reader : permet de rechercher des lecteur de carte en completant une structure
card_reader_t qui contient les informations pour pouvoir lister et se connecter a une carte

input :
    card_reader_t ** : structure qui serat remplit des informations si pas d'erreur
                       sinon serat initialise a NULL

output:
	_SUCCESS_                    : si pas d'erreur
	_NOT_NULL_                   : si cardReader est deja initialise (si pas NULL)
	_MOLLOC_ERROR_               : en ca d'erreur d'allocation de memoire
	SCARD_E_INVALID_PARAMETER    : si le Ph context est NULL
	SCARD_E_INVALID_VALUE        : si le type de scope est invalide
	SCARD_E_NO_MEMORY            : probleme d'allocation
	SCARD_E_NO_SERVICE           : le serveur n'est pas alume
	SCARD_F_COMM_ERROR           : erreur de communication interne
	SCARD_F_INTERNAL_ERROR       : erreur interne
	SCARD_E_INSUFFICIENT_BUFFER  : Si la taille du buffer n'est pas suffisant
	SCARD_E_INVALID_HANDLE       : si le scope handle est incorecte
	SCARD_E_NO_READERS_AVAILABLE : si pas de lecteur pret
*/
int find_card_readers(card_reader_t **cardReader) {
	LONG rv;

	if (*cardReader != NULL) return (int)_NOT_NULL_;

	*cardReader = malloc(sizeof(card_reader_t));
	if (*cardReader == NULL) return (int)_MOLLOC_ERROR_;

	memset(*cardReader, 0, sizeof(card_reader_t));

	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &( (*cardReader)->hContext ));
	if (rv != SCARD_S_SUCCESS) {
		free(*cardReader);
		*cardReader = NULL;
		return (int)rv;
	}

	#ifdef SCARD_AUTOALLOCATE
		(*cardReader)->dwReaders = SCARD_AUTOALLOCATE;

		rv = SCardListReaders(
			(*cardReader)->hContext,
			NULL,
			(LPTSTR)&(*cardReader)->mszReaders,
			&(*cardReader)->dwReaders
		);
		if (rv != SCARD_S_SUCCESS) {
			free(*cardReader);
			*cardReader = NULL;
			return (int)rv;
		}
	#else
		rv = SCardListReaders((*cardReader)->hContext, NULL, NULL, &(*cardReader)->dwReaders);
		if (rv != SCARD_S_SUCCESS) { free(*cardReader); *cardReader = NULL; return (int)rv; }

		(*cardReader)->mszReaders = calloc((*cardReader)->dwReaders, sizeof(char));
		
		rv = SCardListReaders(
			(*cardReader)->hContext,
			NULL,
			(*cardReader)->mszReaders,
			&(*cardReader)->dwReaders
		);
		if (rv != SCARD_S_SUCCESS) { free(*cardReader); *cardReader = NULL; return (int)rv; }
	#endif

	return (int)_SUCCESS_;
}

/*
connect_to_card permet d'etablire une connection avec une carte via un lecteur de carte
pour cela il faut utiliser la structure construite avec la fonction find_card_readers.

input :
	card_reader_t ** : structure qui contient les informations sur la connection
	                   du lecteur de carte

output:
	_SUCCESS_                   : si pas d'erreur
	_NOT_INITIALISATED_         : si la structure cardReader n'est pas initialise
	SCARD_E_INVALID_HANDLE      : si le handle est invalide
	SCARD_E_INVALID_PARAMETER   : si les parametres sont invalide
	SCARD_E_INVALID_VALUE       : si les valeurs sont invalides
	SCARD_E_NO_SERVICE          : si il n'y a pas de service
	SCARD_E_NO_SMARTCARD        : si il n'y a pas de cart
	SCARD_E_PROTO_MISMATCH      : si le protocole est inconnue
	SCARD_E_READER_UNAVAILABLE  : si le lecteur ou la carte ne peut etre interroger
	SCARD_E_SHARING_VIOLATION   : si lecteur ou carte deja utilise les droits prioritere
	SCARD_E_UNKNOWN_READER      : si le lecteur n'est pas reconnue ou null
	SCARD_E_UNSUPPORTED_FEATURE : si le protocole n'est pas supporte
	SCARD_F_COMM_ERROR          : si erreur de communication interne
	SCARD_F_INTERNAL_ERROR      : si erreur interne
	SCARD_W_UNPOWERED_CARD      : si la carte n'est pas allimente
	SCARD_W_UNRESPONSIVE_CARD   : si la carte ne dialogue pas
*/
int connect_to_card(card_reader_t **cardReader) {
	LONG rv;

	if (*cardReader == NULL) return (int)_NOT_INITIALISATED_;

	rv = SCardConnect(
		(*cardReader)->hContext,
		(*cardReader)->mszReaders,
		SCARD_SHARE_SHARED, 
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&( (*cardReader)->hCard ),
		&( (*cardReader)->dwActiveProtocol)
	);
	if (rv != SCARD_S_SUCCESS) { free(*cardReader); cardReader = NULL; return (int)rv; }

	switch((*cardReader)->dwActiveProtocol) {
		case SCARD_PROTOCOL_T0:
			(*cardReader)->pioSendPci = *SCARD_PCI_T0; break;
		case SCARD_PROTOCOL_T1:
			(*cardReader)->pioSendPci = *SCARD_PCI_T1; break;
	}

	return _SUCCESS_;
}