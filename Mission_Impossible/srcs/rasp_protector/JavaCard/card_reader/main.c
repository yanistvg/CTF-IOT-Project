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
#include "lib/headers/return_code.h"

int main(void) {
	card_reader_t *cardReader = NULL;

	find_card_reader(&cardReader);

	if (cardReader == NULL) return 1;

	printf("reader name: %s\n", cardReader->mszReaders);

	return 0;
}