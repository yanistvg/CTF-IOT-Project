#!/bin/bash

######################################################
# Fichier de configuration automatique pour la       #
# Raspberry PI qui joue le role de camera            #
######################################################

# définition des varibles pour la mise en place du systeme
rootpwd=5aY3AHyq6
userpwd=8zE4MSku3

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

/usr/bin/apt update -y > /dev/null
cmd_generate_error "update du systeme" "true" "true"
/usr/bin/apt upgrade -y > /dev/null
cmd_generate_error "upgrade du systeme" "true" "true"

##
### Faire la configuration de la camera
### avec la commande rasp-config pour
### ne pas avoir d'intéraction utilisateur
##
### Manipulation a realiser par les utilisateur car
### probleme de configurationa avec la commande echo
### pour donner des characteres
##

/usr/bin/apt install -y motion > /dev/null
cmd_generate_error "Installation de Motion" "true" "true"

# rendre le module camera compatible avec motion
/usr/sbin/modprobe bcm2835-v4l2
cmd_generate_error "activation du modprobe bcm2835-v4l2" "true" "false"
/usr/bin/echo "bcm2835-v4l2" | /usr/bin/tee -a /etc/modules
cmd_generate_error "activation au demarrage du modprobe bcm2835-v4l2" "true" "false"

# dossier pour les logs de motion
/usr/bin/mkdir /home/motion > /dev/null
cmd_generate_error "Creation d'un repertoire pour les logs motion" "true" "true"
/usr/bin/chown motion:motion /home/motion > /dev/null
cmd_generate_error "Affectation du repertoire a motion" "true" "true"

##
### Faire les changements dans le fichier de configuration
### de motion /etc/motion/motion.conf
##
/usr/bin/sed -i "s/daemon off/daemon on/" /etc/motion/motion.conf
cmd_generate_error "Configuration Motion: daemon on" "true" "false"
/usr/bin/sed -i "s/log_file \/var\/log\/motion\/motion.log/log_file \/home\/motion\/motion.log/" /etc/motion/motion.conf
cmd_generate_error "Configuration Motion: log_file" "true" "false"
/usr/bin/sed -i "s/webcontrol_localhost on/webcontrol_localhost off/" /etc/motion/motion.conf
cmd_generate_error "Configuration Motion: daemon webcontrol_localhost" "true" "false"
/usr/bin/sed -i "s/stream_localhost on/stream_localhost off/" /etc/motion/motion.conf
cmd_generate_error "Configuration Motion: stream_localhost" "true" "false"

# demarrage de motion et rendre percistant au demarrage
/usr/bin/systemctl enable motion.service
cmd_generate_error "Activation de motion au demarrage" "true" "false"
/usr/bin/systemctl start motion.service
cmd_generate_error "Demarrage de motion" "true" "false"

/usr/bin/sed -i "s/# By default this script does nothing./motion/" /etc/rc.local
cmd_generate_error "Edition de rc.local" "true" "false"

motion

# changement des mots de passe des utilisateurs
/usr/bin/echo -e "$rootpwd\n$rootpwd\n" | /usr/bin/passwd root
cmd_generate_error "Changement du mot de passe root" "true" "false"
/usr/bin/echo -e "$userpwd\n$userpwd\n" | /usr/bin/passwd user
cmd_generate_error "Changement du mot de passe user" "true" "false"

##
### Configurer le reseau pour etre compatible avec la borne
### wifi.
##
/usr/bin/echo "" >> /etc/network/interfaces
/usr/bin/echo -e "auto eth0" >> /etc/network/interfaces
/usr/bin/echo -e "iface eth0 inet static" >> /etc/network/interfaces
/usr/bin/echo -e "	address 192.168.1.2" >> /etc/network/interfaces
/usr/bin/echo -e "	netmask 255.255.255.248" >> /etc/network/interfaces
/usr/bin/echo -e "	gateway 192.168.1.1" >> /etc/network/interfaces

/usr/bin/systemctl restart networking.service

# redemarrage du systeme
/usr/sbin/reboot