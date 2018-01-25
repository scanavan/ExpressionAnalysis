# Proof-of-concept
import cv2
import sys
from constants import *
from emotion_recognition import EmotionRecognition
import numpy as np
from PIL import Image
from pathlib import Path
import csv

cascade_classifier = cv2.CascadeClassifier(CASC_PATH)

def brighten(data,b):
     datab = data * b
     return datab    

def format_image(image):
  if len(image.shape) > 2 and image.shape[2] == 3:
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
  else:
    image = cv2.imdecode(image, cv2.CV_LOAD_IMAGE_GRAYSCALE)
	
  # Resize image to network size
  try:
    image = cv2.resize(image, (SIZE_FACE, SIZE_FACE), interpolation = cv2.INTER_CUBIC) / 255.
  except Exception:
    print("[+] Problem during resize")
    return None
  # cv2.imshow("Lol", image)
  # cv2.waitKey(0)
  return image

# Load Model
network = EmotionRecognition()
network.build_network()

video_capture = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_SIMPLEX

pathlist = Path(SAVE_DIRECTORY).glob('**/*.jpg')
f = open(CSV_SAVE_DIRECTORY+'result_emotions.csv', 'w')
with f:
  writer = csv.writer(f)
  for filename in pathlist:
    frame2 = np.array(Image.open(str(filename)))
    format_image(frame2)
    result2 = network.predict(format_image(frame2))
    if result2 is not None:
      for index, emotion in enumerate(EMOTIONS):
        cv2.putText(frame2, emotion, (10, index * 20 + 20), cv2.FONT_HERSHEY_PLAIN, 0.5, (0, 255, 0), 1);
        cv2.rectangle(frame2, (130, index * 20 + 10), (130 + int(result2[0][index] * 100), (index + 1) * 20 + 4), (255, 0, 0), -1)
      temp_arr = (str(filename)).split("\\")
      print("emotion",temp_arr[len(temp_arr)-1], EMOTIONS[result2[0].argmax()])
      arr_emotion = [temp_arr[len(temp_arr)-1], EMOTIONS[result2[0].argmax()]]
      writer.writerow(arr_emotion)