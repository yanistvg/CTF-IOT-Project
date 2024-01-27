# Keylogger

Sommaire:

1. [Introduction](#introduction)
2. [Mise en place du Keylogger](#mise-en-place-du-keylogger)
    - [Transmition du code aux différentes cartes](#transmition-du-code-aux-différentes-carte)
        - [ESP32](#esp32)
        - [Carte Arduino DUE](#carte-arduino-due)
        - [Carte Leonardo](#carte-leonardo)
    - [Montage du keylogger](#montage-du-keylogger)
3. [Fonctionnement du Keylogger](#fonctionnement-du-keylogger)
4. [Explication de l'utilisation du keylogger](#explication-de-l'utilisation-du-keylogger)
    - [Intercepter des touches du PC cible](#intercepter-des-touches-du-pc-cible)
    - [Rejouer les touches interceptées du PC cible](#rejouer-les-touches-interceptées-du-pc-cible)
    - [Compiler un programme speudokeylog en keylog](#compiler-un-programme-speudokeylog-en-keylog)
    - [Utiliser le fichier keylog pour injecter des touches sur le PC cible](#utiliser-le-fichier-keylog-pour-injecter-des-touches-sur-le-pc-cible)

## Introduction

Pour cette partie, nous allons faire un keylogger. Un keylogger permet d'être branché à l'intermédiaire d'un clavier et permet de récupérer toutes les touches qu'un utilisateur appuie sur le clavier.

```text
/!\ Ce projet est réalisé par but d'apprentissage et, en aucun cas,
ce projet ne doit pas être détourné pour des utilisations autres que
sur du matériel personnel.

Le piratage est interdit et l'ajout d'un keylogger sur du matériel qui ne nous appartient pas est puni par les lois.
```

## Mise en place du Keylogger

Pour le keylogger que nous avons réalisé, il faut disposer de trois cartes programmables différentes :

- Une carte Arduio DUE
- Une carte Leonardo
- Un ESP32

Vous devez aussi disposer d'un `câble série` pour la carte Leonardo, et un `câble OTG` pour  la carte `Arduino DUE`

### Transmition du code aux différentes cartes

#### ESP32

Pour mettre en place l'`ESP32`, il faut commencer par suivre le tutoriel disponible par ce lien [`https://randomnerdtutorials.com/getting-started-with-esp32/`](https://randomnerdtutorials.com/getting-started-with-esp32/) pour pouvoir utiliser l'IDE Arduino pour téléverser du code sur l'ESP32.

Une fois cela effectué, il faut ouvrir le code disponible dans le repos github : [`src/esp32_code/esp32_code.ino`](./src/esp32_code/esp32_code.ino)

Ensuite, il suffit de cliquer sur le bouton de la `fleche orienté vers la droite`, pour transmettre le code dans la carte.

#### Carte Arduino DUE

Pour pouvoir compiler le code pour la carte Arduino DUE, il faut installer la librairie de l'image ci-dessous.

![due lib install](./picture_project/19_due_lib_install.png)

Une fois cette librairie installée il suffit d'ouvrir le code [`src/due_board_code/due_board_code.ino`](./src/due_board_code/due_board_code.ino), et de choisir la carte DUE comme l'image ci-dessous.

![select due](./picture_project/20_due_config.png)

Il suffit maintenant de téléverser le code en cliquant sur le bouton de la `fleche orienté vers la droite`, pour transmettre le code dans la carte.

#### Carte Leonardo

La carte Arduino est prise en compte par défaut par l'IDE Arduino. Il suffit de choisir le port série de la carte, puis de choisir la carte Leonardo. Le code est disponible : [`src/leonardo_board_code/leonardo_board_code.ino`](./src/leonardo_board_code/leonardo_board_code.ino)

![select Leonardo](./picture_project/18_leonardo_config.png)

Il suffit maintenant de téléverser le code en cliquant sur le bouton de la `fleche orienté vers la droite`, pour transmettre le code dans la carte.

### Montage du keylogger

Le montage des différentes cartes doit être réalisé comme sur l'image ci-dessous.

![montage](./picture_project/17_keylogger_assembly.png)

Le partage de l'alimentation par la `Carte Leonoardo` fonctionne pour l'`ESP32`, mais il est possible de devoir ajouter un câble d'alimentation pour la `Carte DUE`

## Fonctionnement du Keylogger

Le keylogger a deux méthodes de fonctionnement. La première permet à un attaquant de pouvoir récupérer les touches que la victime va presser. Le schéma suivant présente cette méthode de fonctionnement.

![keylogger fonc 1](./picture_project/13_send_char_from_keyboard.png)

La seconde méthode de fonctionnement permet à l'attaquant de transmettre des touches au PC. Le schéma suivant présente ce fonctionnement.

![keylogger fonc 2](./picture_project/12_send_char_from_hacker.png)

## Explication de l'utilisation du keylogger

Pour pouvoir utiliser le keylogger il faut utiliser le code du [`keylogger_client`](./src/keylogger_client) disponible dans les sources. Les explications de l'utilisation du code est disponible dans le répertoire du client et ne va pas être détaillé dans cette partie. Toutefois, nous allons visualiser ce qu'il est possible de faire avec le keylogger et le client.

Pour mettre en place le keylogger, il faut brancher le clavier du PC cible à la `carte DUE`, puis brancher la `carte Leonardo` au PC (pour des soucie d'allimentation est recommender de brancher les trois cartes au PC pour les allimenter).

Nous avons remarquez certain comportement vis à vis du keylogger :
- Si lors de l'appuie de la touche pour activer le pad numérique la lumière ne s'allume pas, il faut appuyer sur le bouton de reset de la `carte DUE`
- Si lors de l'envoie d'une touche avec un mode telque `Shift + a`, ne donne pas un `A`, il faut appuyer sur le bouton de reset de la `carte Leonardo`
- Lors du branchement des différentes carte, si la `carte Leonardo` est branché en premier, il resque d'y avoir des touches qui se déclanche en boucle, il faut donc brancher les autres carte (surtout l`ESP32`), puis appuyer sur le bouton de reset de la `carte Leonardo`

Pour pouvoir utiliser le keylogger, une fois que ce dernier est branché, il faut se connecter au réseau Wifi `Keylogger-wifi` qui est rendu accéssible avec le mot de passe `Azerty1234`.

Nous allons mainteant passer en revue ce qu'il est possible de faire avec ce projet de keylogger.

### Intercepter des touches du PC cible

Dans un premier tant, nous pouvons utiliser le [`keylogger_client`](./src/keylogger_client) pour enregistrer les touches qu'une personne sur le PC cible utilise. Pour cela il faut utiliser la commande suivante :

```bash
./keylogger-client -t 192.168.4.1  -p 9999
```

Par defaut l'adresse IP et le port du serveur auquel le client dois se connecter est le même que pour cette commande. Cette commande va se connecter au serveur puis enregistrer toutes les touches que l'utilisateur du PC cible a utiliser. Ces touches vont être enregistrées dans un fichier `.keylog` qui est un format utilisé pour ce projet.

***La vidéo suivante montre l'utilisation de cette commande***

[![video keylogger part 1](https://img.youtube.com/vi/zc8F7gY7bX4/0.jpg)](https://youtu.be/zc8F7gY7bX4)

Dans cette vidéo, nous pouvons constater que les touches utilisées sur le PC cible sont afficher sur le PC attaquant avec un affichage particulier pour les combinaisons de touches ou de suppression (affichage de `<DEL>` au lieux de supprimer le caractère sur le terminal).

### Rejouer les touches interceptées du PC cible

Une fois que nous avons récupéré le fichier `.keylog`, il est possible par le formatage du fichier et le [`keylogger_client`](./src/keylogger_client) de rejouer exactement ce qui a étais enregistré avec les même delais entre chaque touche. Pour cela il faut utiliser la commande :

```bash
./keylogger-client -r out.keylog
```

***La vidéo suivante montre l'utilisation de cette commande avec l'enregistrement réalisé dans la premier vidéo***

[![video keylogger part 2](https://img.youtube.com/vi/wj1edCbyJe8/0.jpg)](https://youtu.be/wj1edCbyJe8)

Il est également possible d'extraire les touches du fichier `.keylog` au format `text` avec la commande :

```bash
./keylogger-client -e out.keylog
OU
./keylogger-client --extract out.keylog
```

Cette dernière va générer un fichier `text` dont le contenue serat identique que sur le terminal, mais cela permet de ne pas avoir de delais d'attente pour avoir le resultat de l'enregistrement.

### Compiler un programme speudokeylog en keylog

Pour aller plus loins avec le keylogger, nous avons voulue avoir la possiblité d'envoyer des touches de l'attaquant vers le PC cible. Pour ce faire, nous devons disposé d'un fichier `.keylog` qui est le format utilisé par le [`keylogger_client`](./src/keylogger_client). Pour simplifier la création d'un fichier `.keylog`, il est possible d'utiliser le langage définie est intitulé `speudokeylog` pour ce projet (la définition de ce language est disponible dans le répertoire [`src/keylogger_client/pseudokeylog`](./src/keylogger_client/pseudokeylog)). Pour pouvoir convertir le format `speudokeylog` en `keylog`, il faut utiliser la commande suivante :

```bash
./keylogger-client -c pseudokeylog/inject.speudokeylog
```

Le fichier en sortie est le même nom que le fichier d'entée avec l'extention en plus `.keylog`. De plus pour vérifier ce que produit le fichier `.keylog` généré, il est possible aussi de le rejouer avec la commande :

```bash
./keylogger-client -r pseudokeylog/inject.speudokeylog.keylog
```

***La vidéo suivante montre l'utilisation de la compilation du speudokeylog en keylog***

[![video keylogger part 3](https://img.youtube.com/vi/UTMSg7ZKPbU/0.jpg)](https://youtu.be/UTMSg7ZKPbU)

### Utiliser le fichier keylog pour injecter des touches sur le PC cible

Maintenant que nous avons généré un fichier au format `keylog`, nous allons via le [`keylogger_client`](./src/keylogger_client) utiliser ce fichier pour l'injecter au keylogger et ainsi le transmettre au PC cible. Pour cela nous pouvons utiliser la commande suivante :

```bash
./keylogger-client -t 192.168.4.1  -p 9999 -i pseudokeylog/inject.speudokeylog.keylog
```

De cette manière nous pouvons injecter les touches tel que nous le visualisons avec le `replay` au PC cible. Il est également possible de récupérer un fichier `keylog` généré lors d'un enregistrement pour le retransmettre au PC cible ce qui permet de généré un sénario d'attaque au préalable, puis de l'appliquer sur une machine avec le keylogger.

***La vidéo suivante montre l'utilisation du fichier keylog généré par la compilation pour transmettre les touches au PC cible***

[![video keylogger part 4](https://img.youtube.com/vi/UZH3sCuxawg/0.jpg)](https://youtu.be/UZH3sCuxawg)
