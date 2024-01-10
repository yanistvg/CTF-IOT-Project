# IHM du lecteur de carte

Sommaire:

- [Présentation des modules](#presentation-des-modules)
- [Câblage des différents élements](#cablage-des-differents-elements)
- [Tranférer le code vers la carte Arduino](#tranferer-le-code-vers-la-carte-arduino)
- [Touche du Keypad](#touche-du-keypad)

Dans cette partie, nous allons voir comment la carte Arduino MEGA est utilisé pour réaliser une IHM pour povoir intéragir avec le lecteur de carte. Le schéma ci-dessous contient la schématisation des pins de la carte Arduino MEGA utilisé dans ce projet.

![arduino mega pinout](./imgs/01_arduino_mega.png "arduino mega pinout")

Cette carte va permettre à l'utilisateur d'une carte à puce de pouvoir entrer un code, puis ensuite de pouvoir avoir un affichage des informations du système de carte à puce.

## Présentation des modules

Pour mettre en place cette IHM, nous disposons d'un keypad

![keypad](./imgs/02_keypad.png "keypad")

Ce dernier sera utiliser par la carte pour récupérer le code de l'utilisateur via ce keypad.

Nous disposons également d'un afficheur LCD qui permet d'afficher les différent messages que la Raspberry PI transmet lors de la communication. Cela permet d'avoir une information pour l'utilisateur.

![lcd](./imgs/03_lcd.png "lcd")

## Câblage des différents élements

Le schéma ci-dessous permet de visualiser le câblage effectuer pour que ce soit compatible avec le code (En cas de changement du câblage, il faut en consaicance modifier le code).

![cablage](./imgs/04_cablage.png "cablage")

## Tranférer le code vers la carte Arduino

Le code à transmettre dans la carte Arduino est disponible dans le répertoire [`arduino_mega_IHM_card_reader`](./arduino_mega_IHM_card_reader/arduino_mega_IHM_card_reader.ino). Il faut donc ouvrir ce programme avec [l'IDE Arduino](https://www.arduino.cc/en/software).

Pour que le code puisse compiler il faut faire les manipulation suivante dans l'IDE Arduino:
`Sketch > Include Library > Add .ZIP Library...`, ensuite une fenétre va s'afficher, il faut ajouter le fichier [`Keypad.zip`](./ressource/Keypad.zip) présent dans le répertoire [`ressource`](./ressource/Keypad.zip).

Une fois cette librairie importé, il ne reste plus qu'à brancher la carte puis Téléverser le code vers cette dernière. De cette manière, l'IHM est donc disponible pour le challenge

## Touche du Keypad

Le Keypad a pour but de transmettre le code de l'utilisateur vers la Raspberry PI. Pour ce faire l'utilisateur selectionne les numéro de son code, puis valide le code avec la touche `A`. Si une erreur à étais faite dans le code, il est possible de supprimer le dernier chiffre avec la touche `D`.
