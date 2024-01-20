/***********************************************************************
* FILENAME :  parser.h
*
* DESCRIPTION :
*       Ce fichier contient les declaration des structures et des fonctions
*       utiliser pour determiner les parametre que l'utilisateur de ce
*       code peut donner pour faire fonctionner le keylogger_client.
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#ifndef __PARSER_H_
#define __PARSER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "returns.h"
#include "colors.h"

// taille des buffer pour les fichiers input et output
#define MAX_SIZE_FILE 100

// definition des flags pour le parser
#define PARSER_FLAG_HELP    0x01
#define PARSER_FLAG_VERBOSE 0x02
#define PARSER_FLAG_OUTPUT  0x04
#define PARSER_FLAG_INTPUT  0x08
#define PARSER_FLAG_TARGET  0x10
#define PARSER_FLAG_PORT    0x20

// strcuture du parser
struct parser_t {
	int  parser;                 // flags des parser
	char output[MAX_SIZE_FILE];  // fichier d'output
	char input[MAX_SIZE_FILE];   // fichier d'input
	char target[MAX_SIZE_FILE]; // IP du serveur
	int  port;                   // port du serveur
};

int  search_parser(const int argc, char **argv);
void parser_man(int genByError);

#endif