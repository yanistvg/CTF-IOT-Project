"""
Cette classe permet de détecter la présence d'une personne à partir d'une image.
L'objectif est de trouver un moyen de détecter une personne en minimisant les
faux positifs et les vrais négatifs autant que possible. Pour ce faire, plusieurs
tests seront effectués avec différentes images et méthodes dans ce répertoire afin
d'identifier la méthode la plus fiable et la moins gourmande en ressources, car le
projet est destiné à être exécuté sur une Raspberry Pi.

TÂCHES À RÉALISER :
	- Détecter la présence d'une ou plusieurs personnes
	  sur une image . . . . . . . . . . . . . . . . . . . . . . . X
	- Sauvegarder les images ayant détecté la présence
	  de personnes  . . . . . . . . . . . . . . . . . . . . . . . X
	- Expérimenter différentes méthodes de détection de
	  présence pour trouver celle la mieux adaptée à une
	  Raspberry Pi, avec les résultats de détection les
	  plus fiables  . . . . . . . . . . . . . . . . . . . . . . . X
"""

import cv2

class HumanDetector:
	def __init__(self):
		self.fullBody_cascade = cv2.CascadeClassifier('/root/protect_door/lib/humanDetector/haarcascade_fullbody.xml')
		self.face_cascade = cv2.CascadeClassifier('/root/protect_door/lib/humanDetector/haarcascade_profileface.xml')
		self.upperBody_cascade = cv2.CascadeClassifier('/root/protect_door/lib/humanDetector/haarcascade_upperbody.xml')

	def identify_human(self, image) -> bool:
		idenfity = False
		arrUpperBody = self.upperBody_cascade.detectMultiScale(image)
		if arrUpperBody != ():
			idenfity = True
			self.draw_rect_image(image, arrUpperBody)

		arrUpperBody = self.face_cascade.detectMultiScale(image)
		if arrUpperBody != ():
			idenfity = True
			self.draw_rect_image(image, arrUpperBody)
			
		arrUpperBody = self.fullBody_cascade.detectMultiScale(image)
		if arrUpperBody != ():
			idenfity = True
			self.draw_rect_image(image, arrUpperBody)

		return idenfity
			

	def draw_rect_image(self, image, positions):
		for (x, y, w, h) in positions:
			cv2.rectangle(image, (x,y), (x+w,y+h), (0,0,255), 2)