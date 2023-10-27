# Rasp protector

## Explication de l'utilisation de cette Raspberry PI

Cette partie permet de faire la mis en place d'une raspberry PI qui va utiliser le flux vidéo de la caméra et identifier la présence d'une personne ou non. La raspberry va utiliser un lecteur de carte à puce pour pouvoir débloquer la porte. Si une personne est présente devant la caméra, il ne faut pas ouvrir la porte même si l'attaque sur le lecteur de carte à fonctionné.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI B+, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Pour mettre en place l'environnement de cette raspberry, il faut utiliser le script dans ce répertoir de manière :

```sh
sh auto-config.sh
```

Le script va utiliser les source de ce repos pour les mettres en place sur le raspberry, et rendre disponible cette machine.
