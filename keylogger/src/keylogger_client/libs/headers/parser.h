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
#define PARSER_FLAG_HELP    0x0001
#define PARSER_FLAG_VERBOSE 0x0002
#define PARSER_FLAG_OUTPUT  0x0004
#define PARSER_FLAG_INTPUT  0x0008
#define PARSER_FLAG_TARGET  0x0010
#define PARSER_FLAG_PORT    0x0020
#define PARSER_FLAG_REPLAY  0x0040
#define PARSER_FLAG_EXPORT  0x0080
#define PARSER_FLAG_CONVERT 0x0100

// strcuture du parser
struct parser_t {
	int  parser;                 // flags des parser
	char output[MAX_SIZE_FILE];  // fichier d'output
	char input[MAX_SIZE_FILE];   // fichier d'input
	char target[MAX_SIZE_FILE];  // IP du serveur
	char replay[MAX_SIZE_FILE];  // fichier de replay
	char exp[MAX_SIZE_FILE];     // fichier a exporter
	int  port;                   // port du serveur
};

int  search_parser(const int argc, char **argv);
void parser_man(int genByError);

#endif