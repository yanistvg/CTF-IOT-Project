/***********************************************************************
* FILENAME :  main.c
*
* DESCRIPTION :
*       Ce code permet d'interagir avec une carte programme en
*       JavaCard, pour faire des requet APDU. Cela permet de faire
*       la simulation d'un badge pour une porte. L'objectif de cela
*       et de faire un CTF pour les attaquant forge une carte qui
*       permet de brutforce des id pour trouver celui qui ouvrira
*       la porte. Pour ce faire l'attaquant disposerat d'une carte
*       d'un employé et/ou du code de la carte (avec un mauvais id)
*       et devrat produire une carte capable d'imiter la carte mais
*       aussi de brutforcer les id.
*
* AUTHOR :    Yanis GENY          START DATE :    15 Nov 2023
************************************************************************/

#include "lib/headers/interactWithReader.h"
#include "lib/headers/interactWithCard.h"
#include "lib/headers/IHM_computer.h"
#include "lib/headers/IHM_arduino.h"
#include "lib/headers/return_code.h"
#include "lib/headers/camDetected.h"

#define ON_RASP 1 // passer a 1 lorque nous executons se code
                  // sans terminal avec les elements de communication
                  // avec un afficher LCD et un digicode

#define ATTEND_ID 11 // id qui va permettre d'ouvrir la porte

int main(void) {
	int returnValue = 0;
	card_reader_t *cardReader = NULL;
	int id;
	char code[5];

	void (*show_msg)(char *);

	if (ON_RASP) {
		// affecter a show_msg la fonction pour transmettre
		// a l'afficher LCD
		init_serial_communication(); // initialise la communication serie avec l'arduino
		show_msg = &(show_message_to_user_arduino);
	} else {
		show_msg = &(show_message_to_user_computer);
	}

	while (1) {

		/* on recupere le code par l'utilisateur */
		if (ON_RASP) {
			// recuperation du code via le digicode
			get_code_from_user_arduino(code);
		} else {
			 // recuperation par le terminal
			get_code_from_user_computer(code);
		}

		/* Si pas de lecteur de carte trouve */
		returnValue = find_card_readers(&cardReader);
		if (returnValue == _SUCCESS_) {

			/* Si il n'y a pas de carte ou de lecteur */
			returnValue = connect_to_card(&cardReader);
			if (returnValue == _SUCCESS_) { // si la connection a une carte c'est bien etablie

				// faire la communication avec la carte pour recupere l'id
				returnValue = made_full_communication_with_card(&cardReader, code, &id);

				if (returnValue == _ERROR_DURING_COMMUNICATION_ ||
					returnValue == _ERROR_CANT_SELECT_APPLET_   ||
					returnValue == _ERROR_DURING_GET_ID_)
					show_msg("Comm with card\0");
				if (returnValue == _ERROR_BAD_PIN_)
					show_msg("Bad PIN\0");

				if (returnValue == _SUCCESS_) {
					if (id == ATTEND_ID) {
						// ouvrir la porte si personnes est devant la camera
						if (camAsDetectcHumain() == _CAM_NOT_DETECT_)
							show_msg("Door open\0");
						else
							show_msg("CAM detect YOU\0");
					} else {
						// l'id n'est pas le bon
						show_msg("Bad ID\0");
					}
				}

				disconnect_to_card(&cardReader);
				disconnect_to_reader(&cardReader);
				cardReader = NULL;
			
			} else {
				show_msg("No card found\0");
				disconnect_to_reader(&cardReader);
				cardReader = NULL;
			}

		} else {
			show_msg("No card reader\0");
		}
	}


	free(cardReader);
	return 0;
}