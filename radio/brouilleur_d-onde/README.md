# Brouilleur d'onde radio

Sommaire:

1. [Introduction](#introduction)
2. [Mise en place du matèriel](#mise-en-place-du-materiel)
3. [Brouillage d'une fréquence radio](#brouillage-dune-frequence-radio)

## Introduction

Dans cette partie de brouillage d'onde, nous allons rendre indisponible un fréquence de radio FM. Pour cela il nous vous simplement une `Raspberry PI` et un fils que nous allons brancher sur une broche GPIO de la `Raspberry PI`

Le code utilisé pour le brouillage est disponible via le lien github : [`https://github.com/markondej/fm_transmitter`](https://github.com/markondej/fm_transmitter). Dans cette partie nous allons utiliser ce code pour essayer de rendre indisponible une fréquence radio.

## Mise en place du matèriel

Pour cette mise en place, il faut suivre les indications du [`github source`](https://github.com/markondej/fm_transmitter) qui contient les informations de branchement du fil sur la `Raspberry PI`

Nous avons donc installer `Raspberry PI OS (Legacy) Lite` sur une `Raspberry PI 3`, puis simplement brancher le fil sur le GPIO 4 de cette dernière

![montage](./medias/01_montage.png)

## Brouillage d'une fréquence radio

Maintenant que le montage est réalisé, nous allons brouiller une fréquence radio en utilisant les étapes du [`github source`](https://github.com/markondej/fm_transmitter) en utilisant la commande:

```bash
sudo ./fm_transmitter -f 89.6 -b 300 acoustic_guitar_duet.wav
```

Cela nous permet de remplacer à la fréquence `89.6` le son transmit en FM par le son `acoustic_guitar_duet.wav`

[![video de test](http://img.youtube.com/vi/T1Tbs9OprG4/0.jpg)](https://youtu.be/T1Tbs9OprG4)
