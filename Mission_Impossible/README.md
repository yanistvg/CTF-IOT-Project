# Mission Impossible

Sommaire:

- [Présentation du CTF](#presentation-du-ctf)
- [Etapes du challenge](#etapes-du-challenge)
- [Arboraissance de cette partie](#arboraissance-de-cette-partie)
- [Fichier de mis en place et de solution](#fichier-de-mis-en-place-et-de-solution)
- [Mise en place du CTF](#mise-en-place-du-ctf)

## Présentation du CTF

Cette partie est un projet qui propose un challenge de type CTF (Capture The Flag) qui à pour objectif de trouver un moyen de hacker le système mis en place pour obtenir un flag. Ce challenge est inspiré des film lors de l'intrution dans un batiment sécurisé, il faut ne pas être détecté par les caméras en changeant le flux vidéo, mais aussi déverouiller les portes d'accès.

## Etapes du challenge

Ce challenge est composé en trois partie :
 - Piratage d'un réseau WIFI pour s'y introduire
 - Scan du réseau pour identifier les différent élements du réseau
 - Détournement d'un flux vidéo pour passer devant une camera et avoir accès physiquement à un lecteur de carte
 - Pirater le système de lecteur de carte pour ouvrir la porte en créant une carte adapté

## Arboraissance de cette partie

L'arboraissance de cette partie est définie ci-dessous
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

Dans les sources, pour chaque équipement se trouve les informations de la mise en place détaillé pour pouvoir mettre en place chaque élement.

## Mis en place du CTF

Pour mettre en place le système, vous pouvez suivre les étapes présent dans le répertoir [srcs](./srcs) qui donne les détail complet de mis en place étapes par étapes avec le matèriel utilisé lors de la création du sujet. Il est possible que le challenge ne soit pas compatible avec d'autres matériel que celui utilisé.
