#!/bin/bash

######################################################
# Fichier de configuration automatique pour la       #
# Raspberry PI qui joue le role de protection de     #
# porte                                              #
######################################################

# définition des varibles pour la mise en place du systeme
rootpwd=sC23Xs2aP
userpwd=NRx326zFd

# Variables de couleur pour l'affichage
cl_red="\033[1;31m"
cl_green="\033[1;32m"
cl_df="\033[0;m"

# cmd_generate_error permet d'afficher un message d'erreur si la commande a
# echoue avec un message donne. Si il n'y a pas d'erreur, la fonction peut
# ecrire un message de succes sauf si le second argument donne est true.
# Nous avons un troisieme argument qui permet de stopper l'execution du
# script en cas d'erreur si la valeur egal a true.
#
# cmd_generate_error <msg personalise> <afficher msg si success> <quitter exec si erreur>
#
# ex : cmd_generate_error "mise a jour du systeme" "true" "true"
cmd_generate_error() {
	if [ $? != 0 ]
	then
		/usr/bin/echo -e "[$cl_red-$cl_df]$cl_red ERROR$cl_df during : $1"
		if [ $3 = "true" ]
		then
			exit
		fi
	else
		if [ $2 = "true" ]
		then
			/usr/bin/echo -e "[$cl_green+$cl_df]$cl_green OK$cl_df during : $1"
		fi
	fi
}

##
## Debut de la mis en place
##

apt update -y > /dev/null
apt upgrade -y > /dev/null

