# Rasp CAM

## Explication de l'utilisation de cette Raspberry PI

Cette raspberry utilise un module camera pour lui permettre de transmettre le flux vidéo. Ce flux vidéo est utilisé par la `Rasp protector` pour déterminer si une personne est présente devant la caméra.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI B, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Il faut créer un utilisateur `user` avec un mot de passe qui n'est pas important (Le mot de passe va être changé par le script). Pour faire l'installation de cette machine il est conseiller de flasher une carte SD pour avoir une machine qui n'a aucun élements. Il faut aussi que la machine soit connecter à un réseau internet fonctionnel. La raspberry utilisé ne dispose pas du WIFI, il faut donc le connecter en filaire. La configuration réseau serat modifier pour pouvoir être intégrer dans le réseau final, donc elle n'aurat plus accès à internet.

Le repos git serat cloné depuis internet, vous pouvez simplement copier le scipt `auto-config.sh` sur la machine pour l'exécuter.

Pour mettre en place l'environnement de cette raspberry, il faut utiliser le script en temps que root disponible dans ce répertoir :

```sh
sh auto-config.sh
reboot
```

Le script va utiliser les source de ce repos pour les mettres en place sur le raspberry, et rendre disponible cette machine.

## Mot de passe de la machine

Le script va changer les mot de passe des utilisateur de la machine, les mots de passe qui seront mis sont définie ci-dessous

| Utilisateur | Mot de passe |
|-------------|--------------|
| root        | 5aY3AHyq6    |
| user        | 8zE4MSku3    |