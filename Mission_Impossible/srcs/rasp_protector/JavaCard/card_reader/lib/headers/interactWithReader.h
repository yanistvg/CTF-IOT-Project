/***********************************************************************
* FILENAME :  interactWithReader.h
*
* DESCRIPTION :
*       Ce fichier contient les declarations des fonctions qui permet
*       d'interagir avec un lecteur de carte. Pour le projet CTF IOT
*       ces fonction seront utile pour interagir avec une carte et
*       ainsi pourvoir ouvrir un porte ou non.
*
* PUBLIC FUNCTIONS :
*       int     find_card_reader(card_reader_t **cardReader)
*       int     connect_to_card(card_reader_t **cardReader)
*       int     disconnect_to_card(card_reader_t **cardReader);
*       int     disconnect_to_reader(card_reader_t **cardReader);
* 
* TO DO:
*       - Verifier la presence d'un lecteur de carte . . . . . . Done
*       - Se connecter au lecteur de carte et attendre le
*         branchement d'une carte  . . . . . . . . . . . . . . . Done
*       - Se connecter a la carte  . . . . . . . . . . . . . . . Done
*       - Detecter la deconnection du lecteur ou de la carte . . Done
*
* AUTHOR :    Yanis GENY          START DATE :    15 Nov 2023
************************************************************************/

#ifdef WIN32
	#undef UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "return_code.h"

#ifdef __APPLE__
	#include <PCSC/winscard.h>
	#include <PCSC/wintypes.h>
#else
	#include <winscard.h>
#endif

#ifdef WIN32
	static char *pcsc_stringify_error(LONG rv) {
		static char out[20];
		sprintf_s(out, sizeof(out), "0x%08X", rv);

		return out;
	}
#endif

#ifndef __INTERACT_WITH_READER_H__
#define __INTERACT_WITH_READER_H__

typedef struct CardReader {
	SCARDCONTEXT     hContext;
	SCARD_IO_REQUEST pioSendPci;
	DWORD            dwReaders;
	LPTSTR           mszReaders;
	SCARDHANDLE      hCard;
	DWORD            dwActiveProtocol;
} card_reader_t;


/* Declaration des fonctions */
int find_card_readers(card_reader_t **cardReader);
int connect_to_card(card_reader_t **cardReader);
int disconnect_to_card(card_reader_t **cardReader);
int disconnect_to_reader(card_reader_t **cardReader);


#endif