# Mission Impossible

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
 |   |                        caméra et identifie la présence de personne
 |   |
 |   |- rasp_cam            : Fichier source pour la raspberry qui est une caméra et
 |   |                        diffuse le flux vidéo
```

Dans les sources, pour chaque équipement se trouve les informations de la mise en place détaillé pour pouvoir mettre en place chaque élement.

## Fichier de mis en place et de solution

Un fichier de mise en place est disponible `A faire` pour visualiser comment le projet à étais mis en place dans sont intégralité avec moin d'explication que dans les répertoires.

Un second fichier `A faire` permet d'avoir les étapes de manière détailler pour résoudre le CTF.

## Mise en place du CTF

Pour mettre en place le CTF, il faut utiliser le script d'installation disponible dans chaque dossier sources. Pour la partie du routeur wifi, il n'est pas scripté, mais les étapes de mis en place que nous avons réalisé sont disponible pour pouvoir le reproduire.
