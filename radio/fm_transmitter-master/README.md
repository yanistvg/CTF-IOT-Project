# FM Transmitter

Transformez votre Raspberry Pi en brouilleur radio. Fonctionne sur tous les modèles de Raspberry Pi.

Il vous suffit de disposer d'un récepteur FM, de connecter un fil d'environ 20 à 40 cm au GPIO4 de la Raspberry Pi (PIN 4 sur l'en-tête GPIO) pour servir d'antenne, et vous êtes prêt à diffuser.

Ce projet utilise la sortie de l'horloge générale pour produire une communication radio à modulation de fréquence. Il s'inspire d'une idée initialement présentée par Oliver Mattos et Oskar Weigl dans le cadre du projet PiFM.

## Installation et utilisation

Pour utiliser ce logiciel, vous devrez compiler l'exécutable. Tout d'abord, installez les dépendances requises :

    sudo apt-get update
    sudo apt-get install make build-essentia

Selon le système d'exploitation (par exemple, Ubuntu Server 20.10), il peut également être nécessaire d'installer les bibliothèques Broadcom :

    sudo apt-get install libraspberrypi-dev

Après avoir installé les dépendances, clonez ce référentiel et utilisez la commande make pour construire l'exécutable :

    cd fm_transmitter
    make

Après une compilation réussie, vous pouvez commencer à émettre en exécutant le programme "fm_transmitter" :

    sudo ./fm_transmitter -f 100.6 acoustic_guitar_duet.wav

## Remarque :

    -f fréquence - Spécifie la fréquence en MHz, 100.0 par défaut si non spécifiée
    acoustic_guitar_duet.wav - Fichier WAV d'exemple, vous pouvez utiliser le vôtre

Autres options :

    -d canal_dma - Spécifie le canal DMA à utiliser (0 par défaut), tapez 255 pour désactiver le transfert DMA, le CPU sera utilisé à la place
    -b bande_passante - Spécifie la bande passante en kHz, 100 par défaut
    -r - Boucle la lecture

Une fois la transmission commencée, réglez simplement un récepteur FM sur la fréquence choisie, vous devriez entendre la lecture.


