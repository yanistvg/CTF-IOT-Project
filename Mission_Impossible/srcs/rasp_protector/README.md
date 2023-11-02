# Rasp protector

## Explication de l'utilisation de cette Raspberry PI

Cette partie permet de faire la mis en place d'une raspberry PI qui va utiliser le flux vidéo de la caméra et identifier la présence d'une personne ou non. La raspberry va utiliser un lecteur de carte à puce pour pouvoir débloquer la porte. Si une personne est présente devant la caméra, il ne faut pas ouvrir la porte même si l'attaque sur le lecteur de carte à fonctionné.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI 4 B, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Il faut créer un utilisateur `user` avec un mot de passe qui n'est pas important (Le mot de passe va être changé par le script). Pour faire l'installation de cette machine il est conseiller de flasher une carte SD pour avoir une machine qui n'a aucun élements. Il faut aussi que la machine soit connecter à un réseau internet fonctionnel. Il est conseillé de la connecter en filaire. La configuration réseau serat modifier pour pouvoir être intégrer dans le réseau final, donc elle n'aurat plus accès à internet.

Le repos git serat cloné depuis internet, vous pouvez simplement copier le scipt `auto-config.sh` sur la machine pour l'exécuter.

Pour mettre en place l'environnement de cette raspberry, il faut utiliser le script dans ce répertoir de manière :

***L'installation d'opencv pour python sur raspberry PI peux prendre beacoup de temps***

```sh
sh auto-config.sh
reboot
```

Le script va utiliser les source de ce repos pour les mettres en place sur le raspberry, et rendre disponible cette machine.

## Mot de passe de la machine

Le script va changer les mot de passe des utilisateur de la machine, les mots de passe qui seront mis sont définie ci-dessous

| Utilisateur | Mot de passe |
|-------------|--------------|
| root        | sC23Xs2aP    |
| user        | NRx326zFd    |
