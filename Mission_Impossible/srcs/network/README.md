# Network

Sommaire:

1. [Configuration du switch WiFi](#1-configuration-du-switch-wifi)
	1. [Configuration du réseau et du DHCP](#11-configuration-du-reseau-et-du-dhcp)
	2. [Configuration du WIFI](#12-configuration-du-wifi)
	3. [Configuration de l'interface admin du switch](#13-configuration-de-linterface-admin-du-switch)
2. [Configuration des raspberry PI](#2-configuration-des-raspberry-pi)
	1. [Configurer la Raspberry PI caméra](#21-configurer-la-raspberry-pi-camera)
	2. [Configurer la raspberry PI protected door](#22-configurer-la-raspberry-pi-protected-door)

Dans cette section, nous explorerons la procédure que nous avons suivie pour configurer les différents éléments en réseau.

## 1. Configuration du switch WiFi

Pour démarrer, nous avions un commutateur WiFi ***Linksys***

![Switch picture](./pictures/01_switch.png "Switch picture")

Nous avons choisi d’utiliser l’adresse de réseau `192.168.1.0` avec un masque de sous-réseau `255.255.255.248` ce qui nous donne $2^{3} - 2 = 6$ adresses IP utilisables pour le projet. Ce nombre d’adresses IP est suffisant, car nous devons inclure le switch, deux Raspberry Pi, laissant ainsi la possibilité d’avoir trois attaquants potentiels.

### 1.1. Configuration du réseau et du DHCP

Nous avons commencé par modifier la configuration des plages d’adresses réseau du commutateur via l’interface d’administration du switch `username :admin; password: admin` par défaut.

![Configuration du DHCP](./pictures/02_config_dhcp.png "Configuration du DHCP")

### 1.2. Configuration du WIFI

Nous avons ensuite réalisé la configuration du wifi en changeant le nom du réseau wifi, puis le mot de passe du réseau.

![Configuration du wifi 1](./pictures/03_config_wireless_name.png "Configuration du wifi 1")

![Configuration du wifi 2](./pictures/04_config_wireless_password.png "Configuration du wifi 2")

Nous avons mis en place le réseau WiFi `CTF-IOT-2SU` avec le mot de passe `2SU-ZP-v9-18`. Pour faciliter l’attaque par bruteforce, nous avons fourni un format dans l’énoncé pour obtenir un mot de passe qui ne se trouve pas dans une liste de mots courants tout en restant relativement court.

### 1.3. Configuration de l'interface admin du switch

Ensuite, nous avons réussi à changer le mot de passe de l’administrateur de l’interface du switch.

![Configuration admin passwd](./pictures/05_config_passwd_admin.png "Configuration admin passwd")

Nous avons défini le mot de passe pour l’administrateur du switch comme `njvn43mf`.

## 2. Configuration des raspberry PI

Dans le projet, deux Raspberry Pi sont utilisées : l’une connectée en WiFi (pour l’attaque sur le WiFi et l’accès au réseau), et l’autre connectée en filaire, qui agira en tant que caméra.

La configuration détaillée des Raspberry Pi pour les intégrer au réseau sera abordée ultérieurement dans le document. Cependant, le script d’installation automatisera cette configuration.

### 2.1. Configurer la Raspberry PI caméra

Pour la Raspberry Pi connectée en filaire, nous avons attribué l’adresse IP `192.168.1.2/29`

```bash
$ cat /etc/network/interfaces
# interfaces(5) file used by ifup(8) and ifdown(8)
# Include files from /etc/network/interfaces.d:
source /etc/network/interfaces.d/*

auto eth0
iface eth0 inet static
	address 192.168.1.2
	netmask 255.255.255.248
	gateway 192.168.1.1

$ systemctl restart networking.service
$ ifconfig eth0
eth0: flag=4163<UP,BROADCAST,MULTICAST> mtu 1500
	inet 192.168.1.2 netmask 255.255.255.248 broadcast 192.168.1.7
	inet6 fe80::8abd:8fe4:579c prefixlen 64 scopeid 0x20<LINK>
	ether b8:27:eb:f2:c3:79 txqueuelen 1000 (Ethernet)
	RX packets 268 bytes 18070 (17.6 KiB)
	RX errors 0 dropped 0 overruns 0 frame 0
	TX packets 300 bytes 29279 (28.5 KiB)
	TX errors 0 dropped 0 overruns 0 carrier 0 collisions 0

$ ping 192.168.1.1 -c3
PING 192.168.1.1 (192.168.1.1) 56(84) bytes of data.
64 bytes from 192.168.1.1: icmp_seq=1 ttl=64 time=1.52 ms
64 bytes from 192.168.1.1: icmp_seq=2 ttl=64 time=1.28 ms
64 bytes from 192.168.1.1: icmp_seq=3 ttl=64 time=1.30 ms

--- 192.168.1.1 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms
rtt min/avg/max/mdev = 1.277/1.363/1.517/0.108 ms
$
```

Après ces étapes, la Raspberry Pi, qui fait office de caméra, est désormais connectée au réseau. Notez que suite à la commande `systemctl restart networking.service`, il se peut que l’adresse IP statiquement attribuée ne soit pas effective immédiatement. Dans ce cas,
un redémarrage de la Raspberry Pi est nécessaire `reboot`.

### 2.2. Configurer la raspberry PI protected door

Pour la Raspberry Pi connectée en WiFi, nous avons attribué l’adresse IP `192.168.1.3/29`

```bash
$ cat /etc/network/interfaces
# interfaces(5) file used by ifup(8) and ifdown(8)
# Include files from /etc/network/interfaces.d:
source /etc/network/interfaces.d/*

allow-hotplug wlan0
iface wlan0 inet static
	address 192.168.1.3
	netmask 255.255.255.248
	gateway 192.168.1.1
wpa-ssid CTF-IOT-2SU
wpa-psk 9f5d38db9f0533b94deb6ccc3af0330fa05a1ea49ee154593492af5af2b64e86

$ systemctl restart networking.service
$ ifconfig wlan0
wlan0: flag=4163<UP,BROADCAST,MULTICAST> mtu 1500
	inet 192.168.1.3 netmask 255.255.255.248 broadcast 192.168.1.7
	inet6 fe80::c8d:4115:6078 prefixlen 64 scopeid 0x20<LINK>
	ether b8:27:eb:b9:42:13 txqueuelen 1000 (Ethernet)
	RX packets 268 bytes 18070 (17.6 KiB)
	RX errors 0 dropped 0 overruns 0 frame 0
	TX packets 300 bytes 29279 (28.5 KiB)
	TX errors 0 dropped 0 overruns 0 carrier 0 collisions 0

$ ping 192.168.1.1 -c3
PING 192.168.1.1 (192.168.1.1) 56(84) bytes of data.
64 bytes from 192.168.1.1: icmp_seq=1 ttl=64 time=1.52 ms
64 bytes from 192.168.1.1: icmp_seq=2 ttl=64 time=1.28 ms
64 bytes from 192.168.1.1: icmp_seq=3 ttl=64 time=1.30 ms

--- 192.168.1.1 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms
rtt min/avg/max/mdev = 1.277/1.363/1.517/0.108 ms
$ ping 192.168.1.2 -c3
PING 192.168.1.1 (192.168.1.1) 56(84) bytes of data.
64 bytes from 192.168.1.1: icmp_seq=1 ttl=64 time=7.27 ms
64 bytes from 192.168.1.1: icmp_seq=2 ttl=64 time=4.65 ms
64 bytes from 192.168.1.1: icmp_seq=3 ttl=64 time=9.90 ms

--- 192.168.1.1 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms
rtt min/avg/max/mdev = 1.277/1.363/1.517/0.108 ms
$
```

La Raspberry Pi dédiée à la protection de la porte est maintenant connectée au réseau. Après la commande  `systemctl restart networking.service` si l’adresse IP statiquement attribuée ne prend pas effet, un redémarrage `reboot` de la Raspberry Pi peut être nécessaire.
