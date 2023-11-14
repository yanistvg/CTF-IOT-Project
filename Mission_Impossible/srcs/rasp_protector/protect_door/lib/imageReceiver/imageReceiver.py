"""
Cette classe permet de récupérer un flux vidéo via une URL. L'objectif est de ne pas maintenir
la connexion active comme dans un flux vidéo classique, mais plutôt d'effectuer une requête pour
chaque image avec un intervalle pour simuler le flux. Cela ouvre la possibilité à un attaquant
de modifier le cache ARP pour être interrogé sur le flux vidéo à la place de la caméra et ainsi
fournir un flux vidéo différent.

TODO :
	- Établir une connexion avec le serveur pour récupérer
	  le flux d'images . . . . . . . . . . . . . . . . . . . . . . . Done
	- Extraire la première image du flux . . . . . . . . . . . . . . Done
	- Mettre fin à la connexion  . . . . . . . . . . . . . . . . . . Done

@Auteur : Yanis Geny
@Date : 27/10/2023
@Version : 1.0
"""

import io
import requests
import cv2
import numpy as np

class ImageReceiver:

	def __init__(self, url: str) -> None:
		self.url = url

	def get_image(self) -> np.ndarray:
		# Établissement de la connexion au flux vidéo
		request = requests.get(self.url, stream=True, timeout=2)
		boundary = self.get_boundary(request.headers['content-type'])

		# Récupération des données brutes pour extraire les octets liés à l'image
		raw_data = io.BufferedReader(request.raw)
		self.skip_to_boundary(raw_data, boundary)
		length = self.parse_length(raw_data)
		raw_image = raw_data.read(length)

		# Fermeture de la connexion avec le flux vidéo
		request.close()

		# Conversion en image OpenCV
		return cv2.imdecode(np.frombuffer(raw_image, dtype=np.uint8), cv2.IMREAD_COLOR)

	def get_boundary(self, content_type: str) -> bytes:
		index = content_type.rfind("boundary=")
		assert index != -1
		return (content_type[index + len("boundary="):] + "\r\n").encode("utf-8")

	def parse_length(self, raw_data) -> int:
		length = 0
		while True:
			line = raw_data.readline()
			if line == b'\r\n':
				return length
			if line.startswith(b"Content-Length"):
				length = int(line.decode('utf-8').split(": ")[1])
				assert length > 0

	def skip_to_boundary(self, raw_data, boundary: bytes):
		for _ in range(10):
			if boundary in raw_data.readline():
				break
		else:
			raise RuntimeError("Limite non détectée :", boundary)
