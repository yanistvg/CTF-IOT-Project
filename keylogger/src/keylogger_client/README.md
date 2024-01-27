# Keylogger Client

Sommaire :

- [Avant propos](#avant-propos)
- [Compiler le client keylogger](#compiler-le-client-keylogger)
- [Format de fichier définie avec ce projet](#format-de-fichier-définie-avec-ce-projet)
- [Paramètres du client keylogger](#paramètres-du-client-keylogger)
- [Exemple de commande utilisable](#exemple-de-commande-utilisable)

## Avant propos

Le client keylogger à étais développé pour pouvoir intéragir avec la keylogger réalisé avec différente carte programmable. Ce programme est devenu un impératif car le fonctionnement du keylogger avec ça dernière version, ne transmet pas un caractère comme dans le prermière version mais une structure qui contient une valeur qui représente toute les touches de contrôle du clavier, et une seconde valeur qui représente la position de la touche préssé. Cela permet aussi au client de faire une interprétation de certaine touches (comme la touche de suppréssion) tandis que ce qui est trasmit au PC cible dois exécuter toute les touches (toujours pour la touche de suppression, il faut bien exécuter la suppression).

## Compiler le client keylogger

Pour que le client soit exécutable, il faut au préalable compiler le code. Pour cela il suffit d'exécuter la commande suivante ***dans ce répertoire***

```bash
$ make
gcc -Wall -c main.c
gcc -Wall -c libs/parser.c
gcc -Wall -c libs/server_interact.c
gcc -Wall -c libs/key_tranform.c
gcc -Wall -c libs/file_io.c
gcc -Wall -o keylogger-client main.o parser.o server_interact.o key_tranform.o file_io.o
$ 
```

## Format de fichier définie avec ce projet

Pour ce projet, deux format de fichier ont étais définie. La première sont les fichiers `.keylog` qui est le format utilisé par le client keylogger pour enregistrer les touches (sauvegarde la structure transmise par le keylogger avec un timestamp) mais aussi le format qui est utilisé pour d'autres options que nous verons dans la partie suivante.

Le seconde format utilisé par le projet est le `.speudokeylog` qui est la définition d'un language qui permet au client keylogger de transformer ce format en `.keylog` pour pouvoir l'exploiter. Ce language est définie dans le répertoire [`pseudokeylog`](./pseudokeylog/). Ce répertoire contient un fichier `README.md` qui permet de définir ce language, un fichier `inject.speudokeylog` qui est un exemple de ce language, et le fichier `inject.speudokeylog.keylog` qui est le fichier de sortie après la compilation du client keylogger.

## Paramètres du client keylogger

Pour présenter les différents paramètres du client keylogger, nous allons identifier les paramètres de connection, puis les paramètres qui peuvent être ajouté à une connexion, puis les paramètres indépendant.

1. ***Paramètre de connexion***

| Syntaxe      | Paramètre         | info                                             |
|:------------:|:-----------------:|:------------------------------------------------:|
| -t, --target | IP du keylogger   | Permet de donner l'IP du serveur du keylogger    |
| -p, --port   | PORT du keylogger | Permet de donner le port du serveur du keylogger |

2. ***Paramètre utilisant une connexion***

| Syntaxe       | Paramètre | info                                                                    |
|:-------------:|:---------:|:-----------------------------------------------------------------------:|
| -o, --output  | FICHIER   | Permet de définir un fichier de sortie de l'enregistrement des touches. Par defaut si ce paramètre n'est pas présent un fichier est créer automatiquement `out.keylog` |
| -i, --input   | FICHIER   | Permet de transmettre des touches du PC de l'attaquant au PC cible. ***Ce mode ne récupére par les touches du PC cible et s'arrête une fois toute les touches transmisent*** |
| -v, --verbose |           | Est utilisé en mode d'écoute, et permet l'affichage sur le sortie standart des touches reçue en temps réel. Si ce paramètre n'est pas activé, les touches seront seulement enregistré dans un fichier de sortie |

3. ***Paramètre intépendant***

| Syntaxe       | Paramètre | info                                                                    |
|:-------------:|:---------:|:-----------------------------------------------------------------------:|
| -r, --replay  | FICHIER   | Ce paramètre permet de rejouer un fichier au format `keylog` qui réalisé lors d'un enregistrement du keylogger ou d'une compilation d'un fichier `speudokeylog` |
| -e, --extract | FICHIER   | Ce paramètre permet d'extraire au format texte le contenue d'un fichier en `keylog`. Le fichier texte contient les même information que le replay, mais il n'interpréte pas les delay d'attente entre chaque touches |
| -c, --convert | FICHIER   | Permet de convertir un fichier au format `speudokeylog` en `keylog`. Si une erreur est détecté lors de la convertion, un message d'erreur indiquant la ligne responsable est affiché sur la sortie standard |

## Exemple de commande utilisable

```bash
./keylogger-client -t 192.168.4.1  -p 9999
  # Permet d'enregistrer les touches transmit par le keylogger sans affichage sur le terminal
./keylogger-client -t 192.168.4.1  -p 9999 -v
  # Permet d'enregistrer les touches transmit par le keylogger avec un affichage sur le terminal

#################################################################################################

./keylogger-client -t 192.168.4.1  -p 9999 -i pseudokeylog/inject.speudokeylog.keylog
  # Permet de transmettre des touches au keylogger

#################################################################################################

./keylogger-client -r out.keylog
  # Permet de rejouer le fichier out.keylog
./keylogger-client -e out.keylog
  # Permet d'extraire dans un fichier texte le contenue de out.keylog

#################################################################################################

./keylogger-client -c pseudokeylog/inject.speudokeylog
  # Permet de convertir un code en speudokeylog en keylog
```
