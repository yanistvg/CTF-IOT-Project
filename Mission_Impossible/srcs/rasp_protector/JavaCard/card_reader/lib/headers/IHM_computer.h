/***********************************************************************
* FILENAME :  IHM_computer.h
*
* DESCRIPTION :
*       Ce fichier contient les declarations des fonctions qui permet
*       d'interagir avec un utilisateur via le terminal pour que ce projet
*       puisse etre realise sur un ordinateur
*
* PUBLIC FUNCTIONS :
*       void    get_code_from_user_computer(char *code_dst);
*       void    show_message_to_user_computer(char *msg);
*
* AUTHOR :    Yanis GENY          START DATE :    17 Nov 2023
************************************************************************/

#ifndef __IHM_COMPUTER_H_
#define __IHM_COMPUTER_H_


#include <stdio.h>

void get_code_from_user_computer(char *code_dst);
void show_message_to_user_computer(char *msg);


#endif