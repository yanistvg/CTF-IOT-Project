"""
Ce code a pour objectif de capturer des images à partir d'un flux vidéo
transmis par une Raspberry Pi équipée d'un module caméra, utilisant le
logiciel Motion pour la transmission vidéo.

Les images capturées seront utilisées pour détecter la présence de
personnes. En cas de détection, le système verrouillera un mécanisme,
permettant ainsi à d'autres programmes de réagir en conséquence. Le code
sera exécuté sur une Raspberry Pi et interagira avec les broches GPIO
pour allumer des LEDs et activer une sirène lorsqu'une détection a lieu.

L'objectif de l'attaquant est de trouver un moyen de rendre ce code inopérant
sans déclencher l'alarme.

TÂCHES À RÉALISER :
	- Capturer les images transmises par le flux de la caméra . . . . . . . Done
	- Détecter la présence de personnes sur les images  . . . . . . . . . . Done
	- Interagir avec les broches GPIO de la Raspberry Pi pour
	  déclencher un signal sonore et visuel en cas de détection . . . . . . Done
	- Enregistrer les personnes détectées pour éventuellement
	  compiler les détections (optionnel) . . . . . . . . . . . . . . . . . X
	- Mettre en place un mécanisme de verrouillage et de déverrouillage . . Done
	- Verrouiller lorsque nous ne pouvons pas joindre le stream . . . . . . Done

@Auteur : Yanis Geny
@Date : 27/10/2023
@Version : 1.0
@Lien : https://github.com/yanistvg/CTF-IOT-Project
"""
import cv2
from lib.imageReceiver.imageReceiver import ImageReceiver
from lib.humanDetector.humanDetector import HumanDetector
from lib.ledIndicator.ledIndicator import LedIndicator
from time import sleep

def main():
	image_receiver = ImageReceiver("http://192.168.1.2:8081")
	human_detector = HumanDetector()
	indicator = LedIndicator()

	try:
		image = image_receiver.get_image()
		if human_detector.identify_human(image):
			indicator.alert_presence()
		else:
			indicator.alert_none()
	except:
		indicator.alert_network()

if __name__ == "__main__":
	main()