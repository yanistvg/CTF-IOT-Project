"""
Ce code permet de declancher le programme de verification de personne devant la camera.
Cette mesure est faite pour cause que lorsque le programme est lancer, lorsque nous
deconnectons la connection de la raspberry pi cam, le code ne detecte pas son inactivite
le fait de le faire via un code de lancement, force le rechargement de la connection
a la camera

@Auteur : Yanis Geny
@Date : 14/11/2023
@Version : 1.0
@Lien : https://github.com/yanistvg/CTF-IOT-Project
"""

import subprocess
from time import sleep

while True:
	subprocess.run("python3 /root/protect_door/main.py")
	sleep(2)
