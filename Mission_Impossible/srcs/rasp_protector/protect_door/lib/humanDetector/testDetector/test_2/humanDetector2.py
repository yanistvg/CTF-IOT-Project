import cv2
import time

class HumanDetector2():
	def __init__(self):
		self.upperBody_cascade = cv2.CascadeClassifier('test_2/haarcascade_upperbody.xml')  

	def identify_human(self, image, i) -> float:
		start = time.time()

		arrUpperBody = self.upperBody_cascade.detectMultiScale(image)
		if arrUpperBody != ():
				for (x, y, w, h) in arrUpperBody:
					cv2.rectangle(image, (x,y), (x+w,y+h), (255,0,0), 2)

		cv2.imwrite(f"test_2/human_found/{i}.jpg", image)

		end = time.time()
		return end - start