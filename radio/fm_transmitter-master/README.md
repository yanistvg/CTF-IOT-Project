FM Transmitter

Transformez votre Raspberry Pi en émetteur FM. Fonctionne sur tous les modèles de Raspberry Pi.

Il vous suffit de disposer d'un récepteur FM, de connecter un fil d'environ 20 à 40 cm au GPIO4 de la Raspberry Pi (PIN 7 sur l'en-tête GPIO) pour servir d'antenne, et vous êtes prêt à diffuser.

Ce projet utilise la sortie de l'horloge générale pour produire une communication radio à modulation de fréquence. Il s'inspire d'une idée initialement présentée par Oliver Mattos et Oskar Weigl dans le cadre du projet PiFM.
Installation et utilisation

Pour utiliser ce logiciel, vous devrez compiler l'exécutable. Tout d'abord, installez les dépendances requises :

sql

sudo apt-get update
sudo apt-get install make build-essential

Selon le système d'exploitation (par exemple, Ubuntu Server 20.10), il peut également être nécessaire d'installer les bibliothèques Broadcom :

arduino

sudo apt-get install libraspberrypi-dev

Après avoir installé les dépendances, clonez ce référentiel et utilisez la commande make pour construire l'exécutable :

bash

git clone https://github.com/markondej/fm_transmitter
cd fm_transmitter
make

Après une compilation réussie, vous pouvez commencer à émettre en exécutant le programme "fm_transmitter" :

bash

sudo ./fm_transmitter -f 100.6 acoustic_guitar_duet.wav

Remarque :

    -f fréquence - Spécifie la fréquence en MHz, 100.0 par défaut si non spécifiée
    acoustic_guitar_duet.wav - Fichier WAV d'exemple, vous pouvez utiliser le vôtre

Autres options :

    -d canal_dma - Spécifie le canal DMA à utiliser (0 par défaut), tapez 255 pour désactiver le transfert DMA, le CPU sera utilisé à la place
    -b bande_passante - Spécifie la bande passante en kHz, 100 par défaut
    -r - Boucle la lecture

Une fois la transmission commencée, réglez simplement un récepteur FM sur la fréquence choisie, vous devriez entendre la lecture.
Raspberry Pi 4

Sur le Raspberry Pi 4, le matériel intégré interfère probablement d'une manière ou d'une autre avec ce logiciel, rendant la transmission impossible sur toutes les fréquences standard de diffusion FM. Dans ce cas, il est recommandé de :

    Compiler l'exécutable avec l'option d'utilisation du GPIO21 au lieu du GPIO4 (PIN 40 sur l'en-tête GPIO) :

go

make GPIO21=1

    Modifier soit les paramètres du régulateur de fréquence du processeur ARM en "powersave", soit les fréquences minimale et maximale du processeur ARM à une valeur constante (voir : https://www.raspberrypi.org/forums/viewtopic.php?t=152692).

bash

echo "powersave"| sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor

    Utiliser des fréquences de diffusion FM plus basses (en dessous de 93 MHz) lors de la transmission.

Utilisation comme périphérique de sortie audio général

hydranix a trouvé une méthode simple pour utiliser l'émetteur comme périphérique de sortie audio général. Pour ce faire, vous devez charger le module "snd-aloop" et diffuser la sortie du périphérique de bouclage vers l'application émetteur :

bash

sudo modprobe snd-aloop
arecord -D hw:1,1,0 -c 1 -d 0 -r 22050 -f S16_LE | sudo ./fm_transmitter -f 100.6 - &

Veuillez noter que le périphérique de bouclage doit être défini comme périphérique ALSA par défaut (voir cet article). Le paramètre "-D hw:X,1,0" doit également pointer vers ce périphérique (utilisez le numéro de carte à la place de "X").
Prise en charge du microphone

Pour utiliser une entrée microphonique en direct, utilisez la commande arecord, par exemple :

bash

arecord -D hw:1,0 -c 1 -d 0 -r 22050 -f S16_LE | sudo ./fm_transmitter -f 100.6 -

En cas de baisse de performances, utilisez plughw:1,0 au lieu de ```hw:
