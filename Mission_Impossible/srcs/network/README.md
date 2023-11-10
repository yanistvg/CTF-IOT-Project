# Network

Dans cette section, nous allons voir comment nous avons fait pour mettre en place les diférents éléments en réseau.

## 1. Configuration du switch WiFi

Pour commencer, nous avions un switch Wifi ***Linksys***

![Switch picture](./pictures/01_switch.png "Switch picture")

Nous avons choisie de prendre comme addresse de réseau `192.168.1.0` avec un masque de sous-réseau `255.255.255.248` ce qui nous donne $2^{3} - 2 = 6$ addresse IP utilisable pour le projet. Ce nombre d'addresse IP est suffisant car nous devons avoir le switch, deux raspberry PI, ce qui laisse trois attaquant possible.

### 1.1. Configuration du réseau et du DHCP

Nous avons commencer par changer la configuration des plages d'adresse réseau du switch via l'interface d'administration du switch `username :admin; password: admin` par défaut.

![Configuration du DHCP](./pictures/02_config_dhcp.png "Configuration du DHCP")

### 1.2. Configuration du WIFI

Nous avons ensuite réalisé la configuration du wifi en changeant le nom du réseau wifi, puis le mot de passe du réseau.

![Configuration du wifi 1](./pictures/03_config_wireless_name.png "Configuration du wifi 1")

![Configuration du wifi 2](./pictures/04_config_wireless_password.png "Configuration du wifi 2")

Nous avons donc le réseau wifi `CTF-IOT-2SU` qui a pour mot de passe `2SU-ZP-v9-18`. Pour l'étape du piratage de ce mot de passe nous donnerons un format dans l'énoncer pour que ce soit plus facile à faire en brutforce, car nous voulions un mot de passe qui n'est pas dans une Wordlists mais qui soit pas trop long avec du brutforcing.

### 1.3. Configuration de l'interface admin du switch

Par la suite, nous avons pu faire le changement du mot de passe de l'admin de l'interface du switch.

![Configuration admin passwd](./pictures/05_config_passwd_admin.png "Configuration admin passwd")

Nous avons donné comme mot de passe pour la partie administrateur du switch `njvn43mf`.

## 2. Configuration des raspberry PI

Dans ce projet, nous avons deux Raspberry PI et nous devons faire en sorte que celle-ci soit dans le même réseau. Il nous faut une raspberry connecté en Wifi (pour pouvoir faire l'attaque sur le wifi et pouvoir se connecter ua réseau), et la seconde connecté en filaire.

La raspberry connecté en filaire serat la camera.

Dans la suite de se document, nous allons voir comment configurer les raspberry PI pour qu'elles soit dans le réseau mais le script d'installation ferrat cette configuration automatiquement.

### 2.1. Configurer la Raspberry PI caméra


Pour cette Raspberry PI, nous voulons avoir la comme addresse IP `192.168.1.3/29`

