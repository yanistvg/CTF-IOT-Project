"""

Ce code permet de faire des tests sur différente methode de faire de l'identification
de personne sur une image. Pour cela, nous avons prit 69 images. Ces images vont étre
utilisé par plusieur methode, pour que nous puissions évaluer laquelle des méthode est
la plus rapide et la plus performante.

Une fois ces test réalisé, nous pourrons utiliser la plus performante pour le projet et
l'implémenter.

Chaque detecteur dois prendre les images une par une, puis identifier la présence d'une
personne. Si elle detect une personne, il faut ajouter un rectangle sur celle-ci. toute
les images vont étre enregistré dans un dossier qui leurs sont propre.

De cette manière, nous pourrons manuellement regarder chaque image pour attribuer un score
sur la détection et enfin déterminer quelle detecteur à le meilleur score.

"""

import cv2
from test_1.humanDetector1 import HumanDetector1
from test_2.humanDetector2 import HumanDetector2
from test_3.humanDetector3 import HumanDetector3
from test_4.humanDetector4 import HumanDetector4
from test_5.humanDetector5 import HumanDetector5
from test_6.humanDetector6 import HumanDetector6

# initialise tous les detecteurs
test1 = HumanDetector1() # test avec le detecteur opencv par defaut
test2 = HumanDetector2() # test avec un fichier xml qui detect le haut du corp
test3 = HumanDetector3() # test avec un fichier xml qui detect le corp en entier
test4 = HumanDetector4() # test avec un fichier xml qui detect un visage
test5 = HumanDetector5() # test avec un fichier xml qui detect un visage
test6 = HumanDetector6() # test avec des fichiers xml des tests precedent

# initialise les tableau pour faire les moyennne de temps de detection
test1_time = []
test2_time = []
test3_time = []
test4_time = []
test5_time = []
test6_time = []

for i in range(70):
	# test chaque méthode avec l'image
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test1_time.append( test1.identify_human(img, i) )
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test2_time.append( test2.identify_human(img, i) )
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test3_time.append( test3.identify_human(img, i) )
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test4_time.append( test4.identify_human(img, i) )
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test5_time.append( test5.identify_human(img, i) )
	img = cv2.imread(f"imgs_src/{i}.jpg") # charge l'image
	test6_time.append( test6.identify_human(img, i) )

print(f"test 1 : {sum(test1_time) / len(test1_time)} ms")
print(f"test 2 : {sum(test2_time) / len(test2_time)} ms")
print(f"test 3 : {sum(test3_time) / len(test3_time)} ms")
print(f"test 4 : {sum(test4_time) / len(test4_time)} ms")
print(f"test 5 : {sum(test5_time) / len(test5_time)} ms")
print(f"test 6 : {sum(test6_time) / len(test6_time)} ms")



"""
➜  testDetector python3 testDetector.py 
test 1 : 0.07309539999280656 ms
test 2 : 0.12978706359863282 ms
test 3 : 0.06085587910243443 ms
test 4 : 0.0822237593787057 ms
test 5 : 0.111064236504691 ms
test 6 : 0.29436661515917095 ms
➜

Lors du lancement du test, nous avons des temps qui sont plutot court.
Le test 6 pocède plusieur fichier xml, ce qui n'augmente le temps mais
peut rester resonable.

Il faut maintenant déterminer quelle test est la plus performante. Pour cela
nous allons parcourir chaque image, et compter le nombre d'erreur faire, et le
nombre de bonne réponse. Nous pourrons faire un ratio pour déterminer lequel est
le plus intéressant. Une même image peut faire une faute et une bonne réponse.
ex: si une personne est détecté et que la seconde ne l'ai pas.
    ou bien si une personne est détecté mais aussi une seconde personne qui n
    n'eest pas présent.


test 1:
	fautes        : 53
	bonne reponse : 42

	beacoup de faute de non detection

test 2:
	fautes        : 53
	bonne reponse : 40

	beacoup de faute de detection de personne sur ces
	objects

test 3:
	fautes        : 62
	bonne reponse : 17

	Très peu de détection de personnes la majorité des bonne réponse
	c'est lorsque qu'il n'y a personne sur l'image et qu'il ne détecte
	personne

test 4:
	fautes        : 52
	bonne reponse : 30

	beacoup de faute du a la non detection lorsque la personne est loin de l'objectif

test 5:
	fautes        : 53
	bonne reponse : 16

	beacoup de faute lorsque les personnes sont de dos ou trop loin

test 6:
	fautes        : 53
	bonne reponse : 42

	Les fautes faites sont les vrai négatif (détection de personne alors qu'il
	n'y en a pas). en regardant les images, nous aurrons plus de chance avec cette
	méthode de détection


La méthode retenue est le test 6, nous avons plus de fois la détection des personnes
avec quand même de vrai négatif. Pour les éviter il faudrait placer la caméra à un
emplacement qui n'a pas de parasite d'objet et à une bonne distance des personnes.


"""