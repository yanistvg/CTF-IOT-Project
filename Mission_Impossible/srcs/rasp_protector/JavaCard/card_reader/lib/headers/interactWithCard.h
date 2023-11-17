/***********************************************************************
* FILENAME :  interactWithCard.h
*
* DESCRIPTION :
*       Ce fichier contient les declarations des fonctions qui permet
*       d'interagir avec une carte. Pour le projet CTF IOT
*       ces fonction seront utile pour interagir avec la carte et
*       ainsi pourvoir ouvrir un porte ou non.
*
* PUBLIC FUNCTIONS :
*       int     APDU_select_applet(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len);
*       int     APDU_valid_pin(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len, char *code);
*       int     APDU_get_id(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len);
*       int     send_APDU_request(card_reader_t **cardReader, BYTE *APDU_src, DWORD APDU_src_len, BYTE *APDU_dst, int *APDU_dst_len);
*       int     made_full_communication_with_card(card_reader_t **cardReader, char *code, int *id);
*
* AUTHOR :    Yanis GENY          START DATE :    17 Nov 2023
************************************************************************/

#ifndef __INTERACT_WITH_CARD_H__
#define __INTERACT_WITH_CARD_H__

#include "interactWithReader.h"

int APDU_select_applet(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len);
int APDU_valid_pin(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len, char *code);
int APDU_get_id(card_reader_t **cardReader, BYTE *APDU_dst, int *APDU_len);
int send_APDU_request(card_reader_t **cardReader, BYTE *APDU_src, DWORD APDU_src_len, BYTE *APDU_dst, int *APDU_dst_len);
int made_full_communication_with_card(card_reader_t **cardReader, char *code, int *id);

#endif