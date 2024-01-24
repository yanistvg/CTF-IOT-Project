# Rasp CAM

Sommaire:

- [Explication de l'utilisation de cette Raspberry PI](#explication-de-lutilisation-de-cette-raspberry-pi)
- [Mise en place de l'environnement](#mise-en-place-de-lenvironnement)
- [Mot de passe de la machine](#mot-de-passe-de-la-machine)

## Explication de l'utilisation de cette Raspberry PI

La Raspberry Pi utilise un module caméra pour transmettre le flux vidéo. Ce flux est exploité par la  `Rasp protector` afin de détecter la présence d’une personne devant la caméra.

## Mise en place de l'environnement

***Pour cette partie, nous disposions d'une raspberry PI B, avec l'OS `Raspberry PI OS (Legacy) Lite`***

Il était nécessaire de créer un utilisateur `user` avec un mot de passe non critique (qui serait modifié ultérieurement par le script). Pour l’installation, il était recommandé de flasher une carte SD pour obtenir une machine sans éléments préexistants. La Raspberry Pi, dépourvue de WiFi, devait être connectée en filaire à un réseau internet fonctionnel.
La configuration réseau serait modifiée pour s’intégrer dans le réseau final, excluant ainsi l’accès à internet.

Avant de débuter l’installation via le script, l’activation du module caméra était requise.
```sh
raspi-config
	# what user should these settings apply to? -> user
	# Interface Options > Legacy Camera > <Yes> > <Ok>
	# une fois terminer appuyer sur echap
```

Maintenant, nous pouvons connecter la caméra à la Raspberry Pi comme illustré dans l’image ci-dessous.

![Cam connected](./imgs/01_rasp_conntec_cam.png "Cam connected")

Pour configurer l’environnement de cette Raspberry Pi, veuillez utiliser le script en tant que superutilisateur (root), disponible dans ce répertoire :

```sh
apt update -y
apt install -y git
cd /tmp/
git clone https://github.com/yanistvg/CTF-IOT-Project.git
cd CTF-IOT-Project/Mission_Impossible/srcs/rasp_cam
sh auto-config.sh
```

Le script utilisera les sources de ce repos pour les mettre en place sur la Raspberry Pi et rendre cette machine disponible.

***Si lors du démarrage le stream vidéo n'est pas disponible vous pouvez executer les commandes suivante pour le rectifier***

```sh
systemctl enable motion.service
pkill motion
systemctl start motion.service
motion
```

## Mot de passe de la machine

Le script modifiera les mots de passe des utilisateurs de la machine. Les nouveaux mots de passe sont définis comme suit :

| Utilisateur | Mot de passe |
|-------------|--------------|
| root        | 5aY3AHyq6    |
| user        | 8zE4MSku3    |
