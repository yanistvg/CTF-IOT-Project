# SpeudoKeyLog

Sommaire:

- [Introduction](#introduction)
- [Compilation et usage d'un fichier speudokeylog](#compilation-et-usage-dun-fichier-speudokeylog)
- [Définition du langage](#définition-du-langage)
	- [Premier paramètre le caractère du clavier](#premier-paramètre-le-caractère-du-clavier)
	- [Deuxième paramétre le delay aprés le précedent](#deuxième-paramétre-le-delay-aprés-le-précedent)
	- [Troisième paramétre les modes](#troisième-paramétre-les-modes)
- [Exemple de speudokeylog](#exemple-de-speudokeylog)

## Introduction

Ce langage permet de creer une suite de caractere qui pourrat etre comprit par le keylogger une fois compiler (fichier keylog) pour pouvoir l'utiliser pour l'envoyer a une cible.

## Compilation et usage d'un fichier speudokeylog

Pour pouvoir compiler un speudokeylog en keylog, il faut utiliser la commande suivante :

```bash
./keylogger-client -c inject.speudokeylog
```

ou

```bash
./keylogger-client --convert inject.speudokeylog
```

Cette execution va donner un fichier `inject.speudokeylog.keylog` qui peut etre utilisé par les commandes suivantes:

```bash
./keylogger-client -i inject.speudokeylog.keylog
./keylogger-client --inject inject.speudokeylog.keylog
```

De plus, il est possible d'utiliser un fichier enregistrer lors d'une capture du keylogger et de l'utiliser comme fichier d'injection ce qui peut permettre d'éviter la comilation. Pour cela l'attaquant peut utiliser le keylogger pour generer un sénario de touches puis utiliser le fichier sur une cible.

Pour finir, il est possible de vérifier ce qui à étais réaliser par la compilation en rejouant le sénario:

```bash
./keylogger-client -r inject.speudokeylog.keylog
./keylogger-client --replay inject.speudokeylog.keylog
```

## Définition du langage

Ce langage utilise une ligne pour définir l'appuie sur une seul touche. Chaque touche suit le format ci-dessous:

`{caractère du clavier sans options}:{delay aprés le précedent}:{liste des options}`

La dernière ligne doit être vide. Ce langage donne les différents paramètre dans une ligne avec comme séparateur `:`, et ne dois pas contenir d'espace. Nous allons matenant passer en revue les différents paramètre d'une ligne.

### Premier paramètre le caractère du clavier

Ce paramètre contient le caractère de la touche à appuyer sans options c'est à dire que pour afficher un `1`, il faut utiliser la touche `&`. Donc il faut utiliser la touche `&`.

De plus, il y a des touches qui ne sont pas affichage, il faut utiliser les chaines ci-dessous pour pouvoir les utiliser :

- `<VER_NUM>`
- `<UP-ARROW>`
- `<DOWN-ARROW>`
- `<LEFT-ARROW>`
- `<RIGHT-ARROW>`
- `<DOWN>`
- `<UP>`
- `<SUPPR>`
- `<FIN>`
- `<ARRET_DEFIL>`
- `<MAJ>`
- `<F1>`
- `<F2>`
- `<F3>`
- `<F4>`
- `<F5>`
- `<F6>`
- `<F7>`
- `<F8>`
- `<F9>`
- `<F10>`
- `<F11>`
- `<F12>`
- `<INSERT>`
- `<ESC>`
- `<DEL>`
- `<TAB>`
- `<GUI>`
- `<NEW_LINE>`

Mise appare toute ces touches, il faut utiliser les touches du clavier standart FR sans options

### Deuxième paramétre le delay aprés le précedent

Ce delay permet de laissez un temps d'attente avant d'appuyer sur la touche. Le temps dois être définie en `microseconde`.

Pour une seconde d'attente le paramètre est à `1000000`.
Pour une miliseconde d'attente le paramètre est à `1000`.

Ce delay permet pour certain script de laisser du temps au PC cible d'interpréter certaine touche par exemple le temps d'ouverture d'un logiciel.

### Troisième paramétre les modes

Les modes permettent de donner les touches de contrôle. La liste de ces paramètres sont définie :

- `LEFT_CTRL`
- `LEFT_SHIFT`
- `ALT`
- `LEFT_CMD`
- `RIGHT_CTRL`
- `RIGHT_SHIFT`
- `ALT_GR`
- `RIGHT_CMD`

Il est possible de donner plusieur options, pour cela il faut les séparer par des `,` mais ne pas avoir d'espaces entre eux.

exemple pour avoir `LEFT_CTRL` et `RIGHT_SHIFT`, la valeur de ce paramètre sera:

`LEFT_CTRL,RIGHT_SHIFT`

## Exemple de speudokeylog

Dans cette section nous allons visualiser un speudokeylog qui permet d'utiliser la chaine `Azerty@123` et de sauvegarder cette entre avec `ctrl+s` et une combinaison de touche pour visuliser la combinaison de plusieur modes. Nous allons placer 100 millisecondes entre chaque touches.

```text
a:100000:LEFT_SHIFT
z:100000:
e:100000:
r:100000:
t:100000:
y:100000:
à:100000:ALT_GR
&:100000:LEFT_SHIFT
é:100000:LEFT_SHIFT
":100000:LEFT_SHIFT
s:100000:LEFT_CTRL
<TAB>:100000:ALT_GR,LEFT_CTRL,LEFT_SHIFT

```

