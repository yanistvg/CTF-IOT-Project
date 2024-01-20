/***********************************************************************
* FILENAME :  server_interact.h
*
* DESCRIPTION :
*       Ce fichier contient les declaration des structures et des fonctions
*       utiliser pour se connecter au serveur ouvert par l'ESP32 et interagir
*       avec le serveur
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#ifndef __SERVER_INTERACT_H_
#define __SERVER_INTERACT_H_

#define NET_BUFFER_SIZE 100

#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <unistd.h>

#include "parser.h"
#include "returns.h"

struct server_interact_t {
	int                sockfd;
	char               buffer[NET_BUFFER_SIZE];
	struct sockaddr_in serveraddr;
};

extern struct parser_t parser;

int init_server_connection(void);
int close_server_connection(void);
int read_keys(void);

#endif