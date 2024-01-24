#include "headers/key_tranform.h"
#include "headers/keymaps.h"

/*
*  tranforme_received_key permet de transformer la touche recue au format
*  que ce programme peut relir. Le cahngement se fait sur l'ajout d'un
*  timestamp
*
*  input :
*    struct receive_key key       -> touche recu
*    struct save_char_t *key_save -> structure a remplire
*
*  output: none
*/
void tranforme_received_key(struct receive_key key, struct save_char_t *key_save) {
	key_save->mod = key.mod;
	key_save->ch = key.ch;
	gettimeofday(&key_save->timestamp, NULL);
}

/*
*  tranforme_received_key_to_key permet de transformer un key lue en save_char_t
*  a une key en receive_key
*
*  input :
*    struct receive_key *key     -> addresse de la structure a remplir
*    struct save_char_t key_save -> touche a convertir
*
*  output: none
*/
void tranforme_received_key_to_key(struct receive_key *key, struct save_char_t key_save) {
	key->mod = key_save.mod;
	key->ch = key_save.ch;
}

/*
*  show_key_on_terminal permet d'afficher la touche appuyer sur le
*  le terminal.
*
*  input :
*    struct receive_key key -> touche recu
*    int fd                 -> file descriptor ou ecrire
*
*  output: none
*/
void show_key_on_terminal(struct receive_key key, int fd) {
	char key_found[20];
	int  func_ret;

	if (key.mod == 0) { // affichage du clavier simple
		func_ret = found_key_on_keymaps(key.ch, &origin_keyboard, key_found);
		if (func_ret == _SUCCESS_) { write(fd, key_found, strlen(key_found)); return; }
		func_ret = found_key_on_keymaps(key.ch, &unchange_keyboard, key_found);
		if (func_ret == _SUCCESS_) { write(fd, key_found, strlen(key_found)); return; }
		write(fd, "<UNDEFINED>", 11);
		return;
	}

	if ((key.mod & LEFT_SHIFT) != 0 && (key.mod & (LEFT_SHIFT ^ 0XFFFF)) == 0) {
		func_ret = found_key_on_keymaps(key.ch, &maj_keyboard, key_found);
		if (func_ret == _SUCCESS_) { write(fd, key_found, strlen(key_found)); return; }
		func_ret = found_key_on_keymaps(key.ch, &unchange_keyboard, key_found);
		if (func_ret == _SUCCESS_) {
			write(fd, "[{LEFT_SHIFT}, ", 15);
			write(fd, key_found, strlen(key_found));
			write(fd, "]", 1);
			return;
		}
		write(fd, "[{LEFT_SHIFT}, <UNDEFINED>]", 27);
		return;
	}

	if ((key.mod & ALT) != 0 && (key.mod & (ALT ^ 0XFFFF)) == 0) {
		func_ret = found_key_on_keymaps(key.ch, &unchange_keyboard, key_found);
		if (func_ret == _SUCCESS_) {
			write(fd, "[{ALT}, ", 8);
			write(fd, key_found, strlen(key_found));
			write(fd, "]", 1);
			return;
		}
		write(fd, "[{ALT}, <UNDEFINED>]", 20);
		return;
	}

	if ((key.mod & ALT_GR) != 0 && (key.mod & (ALT_GR ^ 0XFFFF)) == 0) {
		func_ret = found_key_on_keymaps(key.ch, &altgr_keyboard, key_found);
		if (func_ret == _SUCCESS_) { write(fd, key_found, strlen(key_found)); return; }
		func_ret = found_key_on_keymaps(key.ch, &unchange_keyboard, key_found);
		if (func_ret == _SUCCESS_) {
			write(fd, "[{ALT GR}, ", 11);
			write(fd, key_found, strlen(key_found));
			write(fd, "]", 1);
			return;
		}
		write(fd, "[{ALT GR}, <UNDEFINED>]", 23);
		return;
	}

	// si le mod n'a pas de transformation dans le code
	write(fd, "[{", 2);
	list_mod_key_terminal(key.mod, fd);
	write(fd, "}, ", 3);
	if (found_key_on_keymaps(key.ch, &origin_keyboard, key_found) == _SUCCESS_) {
		write(fd, key_found, strlen(key_found));
		write(fd, "]", 1);
	}
	else if (found_key_on_keymaps(key.ch, &unchange_keyboard, key_found) == _SUCCESS_) {
		write(fd, key_found, strlen(key_found));
		write(fd, "]", 1);
	}
	else {
		write(fd, "<UNDEFINED>]", 12);
	}
}

/*
*  list_mod_key_terminal permet d'afficher les touches de mode
*  appyer, le mod est transmit avec la touche
*
*  input :
*    int mod -> valeur du mod transmit
*    int fd  -> file descriptor ou ecrire
*
*  output: none
*/
void list_mod_key_terminal(int mod, int fd) {
	int firt = 1;

	if ((mod & LEFT_CTRL  ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "LEFT CTRL", 9);
	}
	if ((mod & LEFT_SHIFT ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "LEFT SHIFT", 10);
	}
	if ((mod & ALT        ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "ALT", 3);
	}
	if ((mod & LEFT_CMD   ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "LEFT CMD", 8);
	}
	if ((mod & RIGHT_CTRL ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "RIGHT CTRL", 10);
	}
	if ((mod & RIGHT_SHIFT) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "RIGHT SHIFT", 11);
	}
	if ((mod & ALT_GR     ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "ALT GR", 6);
	}
	if ((mod & RIGHT_CMD  ) != 0) {
		if (firt) { firt=0; }
		else write(fd, ", ", 2);
		write(fd, "RIGHT CMD", 9);
	}
}

/*
*  found_key_on_keymaps permet de trouver une touche si elle est presente
*  dans le keymaps donner en parametre
*
*  input :
*    int key_value -> valeur de la touche
*    struct keymaps_t *keymap -> addresse d'un keymap definit dans keymaps.h
*    char *key                -> valeur a ecrire dans cette variable
*
*  output:
*    _KEY_NOT_FOUND_ -> si la touche n'est pas presente dans keymap
*    _SUCCESS_       -> si la touche est trouve
*/
int found_key_on_keymaps(int key_value, struct keymaps_t *keymap, char *key) {
	int i = -1;
	while (keymap->keymap[++i].key_value != 0) {
		if (keymap->keymap[i].key_value == key_value) {
			strcpy(key, keymap->keymap[i].char_convert);
			return _SUCCESS_;
		}
	}
	return _KEY_NOT_FOUND_;
}