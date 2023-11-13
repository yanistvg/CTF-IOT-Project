"""
Cette classe permet d'intéragir avec les GPIO de la raspberry PI pour avoir des indicateurs
de la reconnaissance de présence. Un GPIO qui indique que rien n'est detecte, un GPIO pour indiquer
la detection, et un dernier indicateur en cas d'erreur avec l'interaction du stream. Avec
une des erreur, un verroue dois etre fait pour les autres processus et dois etre retire lorsqu'il
n'y a plus d'erreur. Le verroue serrat un fichier dans /tmp/. L'existance de ce fichier signifie
que le verroue est actif.

TODO :
	- Paramettrer les GPIO  . . . . . . . . . . . . . . . . . . Done
	- allumer les GPIO en fonction de l'erreur déclanché  . . . Done
	- Erreur critique, creer un verroue . . . . . . . . . . . . X
	- Enlever le verroue lorsqu'il n'y a pas d'erreur . . . . . X

@Auteur : Yanis Geny
@Date : 31/10/2023
@Version : 1.0
"""
import RPi.GPIO as io
from time import sleep
import subprocess

class LedIndicator():
	
	def __init__(self) -> None:
		self.gpio = {"no_presence": 33, "net_error": 35, "human_detected": 37}
		self.lock = False
		io.cleanup()
		io.setmode(io.BOARD)

		# animation de demarrage
		for i in self.gpio:
			io.setup(self.gpio[i], io.OUT)
			io.output(self.gpio[i], 1)
			sleep(0.5)
		for i in self.gpio:
			io.setup(self.gpio[i], io.OUT)
			io.output(self.gpio[i], 0)
			sleep(0.5)
		self.locked_door(False)
		self.alert_none()

	def alert_none(self) -> None:
		io.setup(self.gpio["no_presence"], io.OUT)
		io.setup(self.gpio["net_error"], io.OUT)
		io.setup(self.gpio["human_detected"], io.OUT)

		io.output(self.gpio["no_presence"], 1)
		io.output(self.gpio["net_error"], 0)
		io.output(self.gpio["human_detected"], 0)

		self.locked_door(False)

	def alert_presence(self) -> None:
		io.setup(self.gpio["no_presence"], io.OUT)
		io.setup(self.gpio["net_error"], io.OUT)
		io.setup(self.gpio["human_detected"], io.OUT)

		io.output(self.gpio["no_presence"], 0)
		io.output(self.gpio["net_error"], 0)
		io.output(self.gpio["human_detected"], 1)

		self.locked_door(True)

	def alert_network(self) -> None:
		io.setup(self.gpio["no_presence"], io.OUT)
		io.setup(self.gpio["net_error"], io.OUT)
		io.setup(self.gpio["human_detected"], io.OUT)

		io.output(self.gpio["no_presence"], 0)
		io.output(self.gpio["net_error"], 1)
		io.output(self.gpio["human_detected"], 0)

		self.locked_door(True)

	def locked_door(self, level_alert: bool) -> None:
		try:
			if level_alert:
				subprocess.call(["touch", "/tmp/protected_door.lock"], shell=True)
			else:
				subprocess.call(["rm", "/tmp/protected_door.lock"], shell=True)
		except:
			pass
