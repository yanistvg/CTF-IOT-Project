import cv2
import time

class HumanDetector1():
	def __init__(self):
		self.hog = cv2.HOGDescriptor()
		self.hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

	def identify_human(self, image, i) -> float:
		start = time.time()

		(humans, _) = self.hog.detectMultiScale(image)

		for (x, y, w, h) in humans:
			pad_w, pad_h = int(0.15 * w), int(0.01 * h)
			cv2.rectangle(image, (x + pad_w, y + pad_h), (x + w - pad_w, y + h - pad_h), (0, 255, 00), 2)

		cv2.imwrite(f"test_1/human_found/{i}.jpg", image)

		end = time.time()

		return end - start