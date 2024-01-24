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
4. [Explication de l'utilisation du keylogger](explication-de-l'utilisation-du-keylogger)

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
