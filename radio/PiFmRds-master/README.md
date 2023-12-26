# Pi-FM-RDS
## Émetteur FM-RDS utilisant le Raspberry Pi

Ce programme génère une modulation FM avec des données RDS (Radio Data System) générées en temps réel. Il peut inclure de l'audio monophonique ou stéréophonique.

Il est basé sur l'émetteur FM créé par Oliver Mattos et Oskar Weigl, puis adapté à l'utilisation du DMA par Richard Hirst. Christophe Jacquet l'a adapté et a ajouté le générateur et le modulateur de données RDS. L'émetteur utilise le générateur PWM du Raspberry Pi pour produire des signaux VHF.

Il est compatible avec le Raspberry Pi 1 (l'original) ainsi qu'avec les Raspberry Pi 2, 3 et 4.

PiFmRds a été développé uniquement à des fins expérimentales. Il ne s'agit pas d'un centre multimédia, il n'est pas destiné à diffuser de la musique sur votre chaîne stéréo.
Comment l'utiliser ?

Pi-FM-RDS dépend de la bibliothèque sndfile. Pour installer cette bibliothèque sur les distributions de type Debian, par exemple Raspbian, exécutez sudo apt-get install libsndfile1-dev.

Pi-FM-RDS dépend également du pilote Linux rpi-mailbox, vous avez donc besoin d'un noyau Linux récent. Les versions de Raspbian à partir d'août 2015 le prennent en charge.

Important. Les binaires compilés pour le Raspberry Pi 1 ne sont pas compatibles avec le Raspberry Pi 2/3, et vice versa. Il est toujours recommandé de recompiler lors du changement de modèle, donc ne sautez pas l'étape make clean dans les instructions ci-dessous !

Clonez le référentiel source et exécutez make dans le répertoire src:

    cd PiFmRds/src
    make clean
    make
    
Important. Si make signale une erreur, aucun fichier exécutable pi_fm_rds n'est généré (et vice versa). Ainsi, toute erreur doit être corrigée avant de passer aux étapes suivantes. make peut échouer si une bibliothèque requise est manquante (voir ci-dessus), ou cela pourrait être un bogue sur une distribution spécifique/récente. Dans ce cas, veuillez signaler un bogue.

Si make ne signale aucune erreur (c'est-à-dire que l'exécutable pi_fm_rds est généré), vous pouvez simplement exécuter:

    sudo ./pi_fm_rds

Cela générera une transmission FM sur 107,9 MHz, avec le nom de station par défaut (PS), le radiotexte (RT) et le code PI, sans audio. Le signal radiofréquence est émis sur GPIO 4 (broche 7 sur l'en-tête P1).

Vous pouvez ajouter de l'audio monophonique ou stéréophonique en référençant un fichier audio comme suit:

    sudo ./pi_fm_rds -audio sound.wav

Pour tester l'audio stéréophonique, vous pouvez essayer le fichier stereo_44100.wav fourni.

La syntaxe plus générale pour exécuter Pi-FM-RDS est la suivante: 

    pi_fm_rds [-freq freq] [-audio file] [-ppm ppm_error] [-pi pi_code] [-ps ps_text] [-rt rt_text]
    
Tous les arguments sont facultatifs :

    -freq spécifie la fréquence porteuse (en MHz). Exemple : -freq 107,9.
    -audio spécifie un fichier audio à jouer. Le taux d'échantillonnage n'a pas d'importance : Pi-FM-RDS le rééchantillonnera et le filtrera. Si un fichier stéréo est fourni, Pi-FM-RDS produira un signal FM stéréo. Exemple : -audio sound.wav. Les formats pris en charge dépendent de libsndfile. Cela inclut WAV et Ogg/Vorbis (entre autres), mais pas MP3. Spécifiez - comme nom de fichier pour lire les données audio sur l'entrée standard (utile pour rediriger l'audio vers Pi-FM-RDS, voir ci-dessous).
    -pi spécifie le code PI de la diffusion RDS. 4 chiffres hexadécimaux. Exemple : -pi FFFF.
    -ps spécifie le nom de la station (nom de service du programme, PS) de la diffusion RDS. Limite : 8 caractères. Exemple : -ps RASP-PI.
    -rt spécifie le texte radio (RT) à transmettre. Limite : 64 caractères. Exemple : -rt 'Hello, world!'.
    -ctl spécifie un tube nommé (FIFO) à utiliser comme canal de contrôle pour changer PS et RT en cours d'exécution (voir ci-dessous).
    -ppm spécifie l'erreur d'oscillateur de votre Raspberry Pi en parties par million (ppm), voir ci-dessous.

En pratique, j'ai constaté que Pi-FM-RDS fonctionne correctement même sans utiliser le paramètre -ppm. Je suppose que les récepteurs sont plus tolérants que ce qui est indiqué dans la spécification RDS.

Une façon de mesurer l'erreur de ppm consiste à lire le fichier pulses.wav : il jouera une impulsion pendant précisément 1 seconde, puis une pause de 1 seconde, et ainsi de suite. Enregistrez la sortie audio à partir d'une radio avec une bonne carte audio. Disons que vous échantillonnez à 44,1 kHz. Mesurez 10 intervalles. À l'aide d' Audacity par exemple, déterminez le nombre d'échantillons de ces 10 intervalles : en l'absence d'erreur d'horloge, cela devrait être 441 000 échantillons. Avec mon Pi, j'ai trouvé 441 132 échantillons. Par conséquent, mon erreur ppm est (441 132-441 000)/441 000 * 1e6 = 299 ppm, en supposant que mon périphérique d'échantillonnage (carte audio) n'a pas d'erreur d'horloge...
Redirection de l'audio vers Pi-FM-RDS

PiFmRds est un programme expérimental, conçu uniquement à des fins expérimentales. Il n'est en aucun cas destiné à devenir un centre multimédia personnel

https://github.com/ChristopheJacquet/PiFmRds
