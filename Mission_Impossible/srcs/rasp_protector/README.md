# Rasp protector

Sommaire:

- [Explication de l'utilisation de cette Raspberry PI](#explication-de-lutilisation-de-cette-raspberry-pi)
- [Mise en place de l'environnement](#mise-en-place-de-lenvironnement)
- [Mot de passe de la machine](#mot-de-passe-de-la-machine)

## Explication de l'utilisation de cette Raspberry PI

Cette section concerne la configuration d’une Raspberry Pi qui utilisera le flux vidéo de la caméra pour détecter la présence d’une personne. La Raspberry Pi sera également équipée d’un lecteur de carte à puce pour déverrouiller la porte. Si une personne est détectée devant la caméra, la porte ne doit pas être ouverte, même si une attaque réussit sur le lecteur de carte.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI 4 B, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Nous devions créer un utilisateur `user` avec un mot de passe temporaire (à modifier ultérieurement via le script). Pour l’installation, il était recommandé de flasher une carte SD pour obtenir une machine vierge. Il était également nécessaire de connecter la Raspberry Pi à un réseau internet fonctionnel, de préférence via une connexion filaire. La configuration réseau était ajustée pour s’intégrer dans le réseau final, excluant l’accès à Internet.

Le dépôt Git étant cloné depuis Internet, mais vous pouvez simplement copier le script `auto-config.sh` sur la machine pour l’exécuter.

Pour configurer l’environnement de la Raspberry Pi, l’utilisation du script dans ce répertoire était nécessaire

***L'installation d'opencv pour python sur raspberry PI peut prendre beaucoup de temps***

```sh
git clone https://github.com/yanistvg/CTF-IOT-Project.git
cd CTF-IOT-Project/Mission_Impossible/srcs/rasp_protector/
sh auto-config.sh
cd ~
rm -rf CTF-IOT-Project
reboot
```

Le script va utiliser les sources de ce repos pour les mettres en place sur le raspberry, et rendre disponible cette machine.

## Mot de passe de la machine

Le script va modifier les mots de passe des utilisateurs de la machine. Les nouveaux mots de passe sont définis comme suit :

| Utilisateur | Mot de passe |
|-------------|--------------|
| root        | sC23Xs2aP    |
| user        | NRx326zFd    |
