#include "headers/IHM_computer.h"

/*
get_code_from_user_computer permet de recuperer un code a quatre chiffre
apprer d'un utilisateur sur un terminal. Le code est un nombre qui est
compose de quatres chiffres.

input :
	char *code_dst : chaine de 4 char qui recevera le code

output:
	none
*/
void get_code_from_user_computer(char *code_dst) {
	int code = 0;
	int i = 4;

	printf("Entrer le code PIN > ");
	fflush(stdin);
	fflush(stdout);
	fscanf(stdin, "%d", &code);

	while (--i >= 0) {
		code_dst[i] = code % 10;
		code /= 10;
	}
	code_dst[4] = 0;
}

/*
show_message_to_user_computer permet d'afficher un message a un utilisateur
par le terminal

input :
	char * : message a afficher

output:
	none
*/
void show_message_to_user_computer(char *msg) {
	printf("%s\n", msg);
}