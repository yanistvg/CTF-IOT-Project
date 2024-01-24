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

struct parser_t parser = {0x00, {0}, {0}, {0}, {0}, {0}};

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

	if (argc <= 1) parser.parser |= PARSER_FLAG_HELP;

	while(++i < argc) {
		// parser du manuel du programme
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			parser.parser |= PARSER_FLAG_HELP;
			continue;
		}
		// parser qui permet d'afficher les touches sur le terminal
		if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
			parser.parser |= PARSER_FLAG_VERBOSE;
			continue;
		}
		// parser qui permet d'avoir un fichier d'enregistrement des touches
		if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
			parser.parser |= PARSER_FLAG_OUTPUT;
			strcpy(parser.output, argv[++i]); // recuperation du nom du fichier
			continue;
		}
		// parser qui permet de donner des touches a transmettre
		if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) {
			parser.parser |= PARSER_FLAG_INTPUT;
			strcpy(parser.input, argv[++i]); // recuperation du nom du fichier
			continue;
		}
		// parser qui donne l'ip du serveur
		if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--target")) {
			parser.parser |= PARSER_FLAG_TARGET;
			strcpy(parser.target, argv[++i]); // recuperation du nom du fichier
			continue;
		}
		// parser qui donne le port du serveur
		if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--port")) {
			parser.parser |= PARSER_FLAG_PORT;
			parser.port = atoi(argv[++i]); // recuperation le port
			continue;
		}
		// parser qui permet de rejoue un fichier de sauvegarde des touches
		if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--replay")) {
			parser.parser |= PARSER_FLAG_REPLAY;
			strcpy(parser.replay, argv[++i]); // recuperation du nom du fichier
			continue;
		}
		// parser qui permet de convertir un fichier de sauvegarde en fichier text
		if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--export")) {
			parser.parser |= PARSER_FLAG_EXPORT;
			strcpy(parser.exp, argv[++i]); // recuperation du nom du fichier
			continue;
		}

		// Si pas de parametre valide arret du programme avec affichage du man
		parser.parser |= PARSER_FLAG_HELP;
		return _BAD_PARAM_;

	}

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
	printf("\t                                 des touches a transmettre au PC cible\n");
	printf("\n");
	printf("%sSi les parametre suivant sont donner, ils seront prioritaire mais%s\n", CYAN, DEFAULT_COLOR);
	printf("%sstoppe la suite de l'excution, ils sont donc a utilise de preference%s\n", CYAN, DEFAULT_COLOR);
	printf("%sun par un par.%s\n", CYAN, DEFAULT_COLOR);
	printf("\t%s-r <FILE>, --replay <FILE>     :%s permet de rejouer un fichier de sauvegarde des touches\n", YELLOW, DEFAULT_COLOR);
	printf("\t                                 en prenant en compte le temps decart de reception\n");
	printf("\t%s-e <FILE>, --export <FILE>     :%s permet d'exporter le fichier de sauvegarde en fichier text\n", YELLOW, DEFAULT_COLOR);
	printf("\n");
	printf("%sParametre d'affichage et d'aide%s\n", CYAN, DEFAULT_COLOR);
	printf("\t%s-v, --verbose                  :%s pour afficher sur le terminal les touches en direct\n", YELLOW, DEFAULT_COLOR);
	printf("\t%s-h, --help                     :%s pour afficher ce man\n", YELLOW, DEFAULT_COLOR);
}