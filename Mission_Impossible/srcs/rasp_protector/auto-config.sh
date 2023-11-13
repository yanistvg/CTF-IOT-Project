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
apt purge wolfram-engine -y >/dev/null
cmd_generate_error "Delation of wolfram-engine" "true" "false"
apt purge libreoffice* -y >/dev/null
cmd_generate_error "Delation of libreoffice" "true" "false"
apt clean -y >/dev/null
cmd_generate_error "apt clean" "true" "false"
apt autoremove -y >/dev/null
cmd_generate_error "apt autoremove" "true" "false"

apt update -y > /dev/null
cmd_generate_error "During update" "true" "true"
apt upgrade -y > /dev/null
cmd_generate_error "During upgrade" "true" "true"

#
## installation de opencv pour raspberry PI
#

# Installation des outils pour opencv
apt install -y build-essential cmake unzip pkg-config >/dev/null
cmd_generate_error "During install build-essential, cmake, unzip, pkg-config" "true" "true"
apt install -y libjpeg-dev libpng-dev libtiff-dev >/dev/null
cmd_generate_error "During install libjpeg-dev, libpng-dev, libtiff-dev" "true" "true"
apt install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev >/dev/null
cmd_generate_error "During install libavcodec-dev, libavformat-dev, libswscale-dev, libv4l-dev" "true" "true"
apt install -y libxvidcore-dev libx264-dev >/dev/null
cmd_generate_error "During install libxvidcore-dev, libx264-dev" "true" "true"
apt install -y libgtk-3-dev >/dev/null
cmd_generate_error "During install libgtk-3-dev" "true" "true"
apt install -y libcanberra-gtk* >/dev/null
cmd_generate_error "During install libcanberra-gtk" "true" "true"
apt install -y libatlas-base-dev gfortran >/dev/null
cmd_generate_error "During install libatlas-base-dev, gfortran" "true" "true"
apt install -y python3-pip > /dev/null
cmd_generate_error "During install python3-pip" "true" "true"

# installation d'opencv
apt install -y python3-opencv
cmd_generate_error "During installation of Opencv for python" "true" "true"


##
### configuration reseau
##

echo -e "" >> /etc/network/interfaces
echo -e "allow-hotplug wlan0" >> /etc/network/interfaces
echo -e "iface wlan0 inet static" >> /etc/network/interfaces
echo -e "	address 192.168.1.3" >> /etc/network/interfaces
echo -e "	netmask 255.255.255.248" >> /etc/network/interfaces
echo -e "	gateway 192.168.1.1" >> /etc/network/interfaces
echo -e "wpa-ssid CTF-IOT-2SU" >> /etc/network/interfaces
echo -e "wpa-psk 9f5d38db9f0533b94deb6ccc3af0330fa05a1ea49ee154593492af5af2b64e86" >> /etc/network/interfaces

systemctl restart networking.service > /dev/null
cmd_generate_error "During network configuration" "true" "false"


