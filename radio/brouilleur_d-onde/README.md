# Brouilleur d'onde radio

Sommaire:

1. [Introduction](#introduction)
2. [Mise en place du matèriel](#mise-en-place-du-materiel)
3. [Brouillage d'une fréquence radio](#brouillage-dune-frequence-radio)
4. [Fonctionnement du brouilleur](#fonctionnement-du-brouilleur)
5. [Acpect légale](#acpect-legale)

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

Cela nous permet de remplacer à la fréquence `89.6` le son transmit en FM par le song `acoustic_guitar_duet.wav`

La vidéo suivante montre le remplacement du song de la radio

[![video de test](http://img.youtube.com/vi/T1Tbs9OprG4/0.jpg)](https://youtu.be/T1Tbs9OprG4)

Un brouilleur de manière normal rend indisponible un service, dans notre cas, nous faisons un remplacement par une autres musique. Si nous voulions réaliser un brouilleur en rendant la radio indisponible, nous aurions du transmettre un song sans audio.

## Fonctionnement du brouilleur

Avec cette démonstration, nous pouvons nous demander comment il est possible de rendre indisponible une station de radio pour remplacer le song.

D'une part, nous avons une antenne radio qui transmet le song de la station de radio. Cette antenne transmet les ondes radios à un certain niveau de puissance qui permet de couvrir un distance importante autour de l'antenne. Lorsque qu'avec la raspberry avec le fils qui joue le rôle d'antenne nous transmettons un song, cetter dernière va recouvrir les ondes transmisent par l'antenne de la station radio.

L'image ci-dessous permet de visualiser le fonctionnement du remplacement des ondes.

![fonctionnement](./medias/02_fonctionnement.png)

Dans cette images, toutes radio brancher sur la fréquence `89.6` étant dans la zone rouge reçeverons le song du brouilleur.

## Dangereusité des brouilleurs

Nous avons vu par cette exemple qu'un brouilleur de demande par beaucoup de matèriel et peut être mis en place facilement et rapidement. Dans cette manipulation nous avons transmit sur des fréquence radio FM une musique, mais que se passerait-il si nous transmettions sur la fréquence de la téléphonie mobile dans un batiment.

Les brouilleurs sont éfficace sur tous systèmes utilisant de la communication sans fils, donc tous les téléphones, les appareil connecté, les télécommandes de garage, et bien d'autres système. Avec un simple brouilleur sur la bonne fréquence, il est possible de rendre indisponible n'importe quelle service.

De plus, nous ne pouvons pas contrer une attaque de brouillage, la seul solution si elle est possible est de sortir de son champs d'action. Néanmain, les brouilleurs sont facilement localisable en déterminant trois points de la bordur du champs d'action du brouilleur, il est possible de trianguliser la source.

## Acpect légale

En france, la détention, l'utilisation, et la commercialisation de dispositif destiné à rendre inopérants des équipements radioélectriques ou des appareils intégrant des équipements radioélectriques de tous types, tant pour l'émission que pour la réception.

En cas d'utilisation d'un brouilleur, la peine encourut est de six mois d'emprisonnement et de 30 000 euros d'amende.

Source de ces information (lors de la rédaction de ces informations):

- [https://www.legifrance.gouv.fr/codes/article_lc/LEGIARTI000024506235/](https://www.legifrance.gouv.fr/codes/article_lc/LEGIARTI000024506235/)
- [https://www.legifrance.gouv.fr/codes/id/LEGIARTI000031318701/2024-01-13/#LEGIARTI000031318701](https://www.legifrance.gouv.fr/codes/id/LEGIARTI000031318701/2024-01-13/#LEGIARTI000031318701)

Il est néanmoins possible d'utiliser des fréquences radio en France, un certain nombre sont dédier pour des stations, et certainne fréquence comme les fréquence Wifi sont soumit à des règles d'utilisation de la fréquence. Il est toutefois possible d'utiliser des fréquences qui ne sont en libre accès.
