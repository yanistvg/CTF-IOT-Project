# Rasp CAM

## Explication de l'utilisation de cette Raspberry PI

Cette raspberry utilise un module camera pour lui permettre de transmettre le flux vidéo. Ce flux vidéo est utilisé par la `Rasp protector` pour déterminer si une personne est présente devant la caméra.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI B, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Pour mettre en place l'environnement de cette raspberry, il faut utiliser le script dans ce répertoir de manière :

```sh
sh auto-config.sh
```

Le script va utiliser les source de ce repos pour les mettres en place sur le raspberry, et rendre disponible cette machine.
