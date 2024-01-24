# Mission Impossible

Sommaire:

- [Présentation du CTF](#presentation-du-ctf)
- [Etapes du challenge](#etapes-du-challenge)
- [Arboraissance de cette partie](#arboraissance-de-cette-partie)
- [Fichier de mis en place et de solution](#fichier-de-mis-en-place-et-de-solution)
- [Mise en place du CTF](#mise-en-place-du-ctf)

## Présentation du CTF

Cette section présente un projet axé sur un défi de type CTF (Capture The Flag), où l’objectif est de hacker un système établi afin d’obtenir un "flag". Le défi tire son inspiration des scénarios de films impliquant l’intrusion dans des bâtiments sécurisés. Les participants doivent éviter d’être détectés par les caméras en altérant le flux vidéo tout en déverrouillant les portes d’accès.

## Etapes du challenge

Ce défi se divise en trois parties :
 - Piratage d'un réseau WIFI pour s'y introduire
 - Scan du réseau pour identifier les différent élements du réseau
 - Détournement d'un flux vidéo pour passer devant une camera et avoir accès physiquement à un lecteur de carte
 - Pirater le système de lecteur de carte pour ouvrir la porte en créant une carte adapté

## Arboraissance de cette partie

Le projet se présente sous l’arboraissance suivante :
```text
Mission_Impossible
 |
 |- srcs                    : Listes des fichiers source utilisé pour le challenge
 |   |
 |   |- rasp_protector      : Fichier source pour la raspberry qui détecte les
 |   |   |                    intrution par la camera
 |   |   |
 |   |   |- protect_door    : Code python qui permet de récupérer le flux vidéo de la
 |   |   |                    caméra et identifie la présence de personne
 |   |   |
 |   |   |- JavaCard        : code lier au lecteur de carte
 |   |   |   |
 |   |   |   |- card_code   : Code en Javacard implementer a une carte pour simuler un
 |   |   |   |                badge d'un ancien employée
 |   |   |   |
 |   |   |   |- card_reader : Code en C qui permet d'interagir avec un lecteur de carte
 |   |   |                    et une carte arduino (qui fait l'IHM). Ce code simule un
 |   |   |                    lecteur de carte pour ouvrir une porte
 |   |
 |   |- rasp_cam            : Fichier source pour la raspberry qui est une caméra et
 |   |                        diffuse le flux vidéo
 |   |
 |   |- network             : Explication de la configuration réseau pour le projet
 |   |
 |   |- IHM_cardreader      : Code pour une arduino qui permet d'avoir une IHM pour
 |                            intéragir avec le lecteur de carte
 |
 |- solution                : Ce dossier contient l'ensemble des solutions d'attaque
 |                            pour ce challenge
 |
 |- sujet                   : Ce dossier contient le sujet pour les personnes qui
                              realise ce challenge. Le sujet est disponible en 
                              Markdown ou en PDF. Il faut aussi avoir l'archive pour
                              pouvoir completer le challenge
```

Dans les sources, pour chaque équipement se trouvent les informations de la mise en place détaillées pour pouvoir mettre en place chaque élément.

## Mise en place du CTF

Pour mettre en place le système, vous pouvez suivre les étapes présentes dans le répertoire [srcs](./srcs) qui donne les détails complets de la mise en place étapes par étapes avec le matériel utilisé lors de la création du sujet. Il est possible que le challenge ne soit pas compatible avec d'autres matériels que celui utilisé.
