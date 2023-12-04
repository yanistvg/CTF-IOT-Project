# Mise en place du challenge Mission Impossible

Pour ce challenge, il y a un certain nombre d'élements physique à mettre en place. Ce fichier permet de donner la procédure pour mettre en place le challenge. Toute les explication détailler sont disponible dans les dossiers de chaque device du challenge.

Ce challenge est schématisable par l'image ci-dessous

![schema du systeme](./imgs/01_schema.png "schema du systeme")

## Liste des élements pour mettre en place le système

Pour pouvoir mettre en place le système il faut au prèalable disposer de plusieur matèriel. L'ensemble des explications de ce système est prévue pour la liste ci-après. En cas de changement de matèriel, il n'est pas obligatoire que les code/script/..., ne fonctionne pas.

La liste des élements pour la mise en place :
 - Routeur Wifi Linksys
 - 2 x Raspberry PI 3 B
 - Carte Arduino MEGA
 - Un afficher LCD (16x2)
 - Un 4x4 Keypad
 - 3 LED (vert, rouge, et orange)
 - un lecteur de carte FEITIAN R301
 - 2 carte à puce
 - un cable ethernet
 - une camera raspberry PI

## Mise en place

Pour faire la mise en place du système, il faut suivre les étapes suivante :
 - Mettre en place le réseau. Pour cela, les étapes que nous avons réalisé sont disponible dans le dossier `network`
 - Mettre en place la camera. Pour cela, les étapes de mise en place de cette partie est disponible dans le dossier `rasp_cam`. Il faut bien brancher la raspberry PI au routeur Wifi et vérifiez la bonne connection avec le routeur (il n'est pas possible de communiquer avec internet dans la configuration de ce challenge).
 - Mettre en place la raspberry door protector. Pour cela il faut suivre les étapes du dossier `rasp_protector`. Il faut aussi vérifier la bonne connection avec le routeur, et la camera.
 - Il faut ensuite mettre en place le code de la carte Arduino MEGA en suivant les étapes du dossier `IHM_cardreader`.
 - Nous pouvons mainteant réaliser une carte d'un ancien emplyée en suivant les étapes du dossier `rasp_protector/JavaCard`
 - Une fois toute ces installations faite, il faut brancher la carte Arduino MEGA sur la raspberry PI `rasp_protector`, et y brancher aussi le lecteur de carte. (Si la carte Arduino n'est pas branché au démarrage de la Raspberry PI, il est possible que le code c'est stopper. Il faut donc faire ces branchement avant de mettre la sous tension, et bien attendre quelle seconde avant de brancher le lecteur de carte)