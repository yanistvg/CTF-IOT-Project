/***********************************************************************
* FILENAME :  returns.h
*
* DESCRIPTION :
*       Ce fichier contient les retours que les fonctions de l'ensemble
*       de ce programme peut generer.
*
* AUTHOR :    Yanis GENY          START DATE :    20 Jan 2024
************************************************************************/

#ifndef __RETURNS_H_
#define __RETURNS_H_

#define _SUCCESS_ 0

// erreur du parser
#define _BAD_PARAM_ 1

// erreur des interaction reseau
#define _SOCKET_ERROR_      1
#define _CONNECT_ERROR_     2
#define _FAIL_CLOSE_SOCKET_ 3
#define _SERVER_NOT_INIT_   4
#define _ERROR_SRV_READ_    5

// erreur file_io
#define _ERROR_OPEN_OUT_FILE_    1
#define _ERROR_FILE_NOT_OPEN_    2
#define _ERROR_WRITE_FILE_       3
#define _ERROR_OPEN_REPLAY_FILE_ 4
#define _ERROR_READING_FILE_     5
#define _KEY_NOT_FOUND_          6

#endif