from constants import *
import pandas as pd
import numpy as np
from PIL import Image

def emotion_to_vec(x):
    d = np.zeros(len(EMOTIONS))
    d[x] = 1.0
    return d

def data_to_image(data):
    #print data
    data_image = np.fromstring(str(data), dtype = np.uint8, sep = ' ').reshape((SIZE_FACE, SIZE_FACE))
    data_image = Image.fromarray(data_image).convert('RGB')
    data_image = np.array(data_image)[:, :, ::-1].copy() 
    data_image = format_image(data_image)
    return data_image

FILE_PATH = 'usfExpressionAnalysis.csv'
data = pd.read_csv(FILE_PATH)

labels = []
images = []
index = 1
total = data.shape[0]
for index, row in data.iterrows():
    #these are all of the changes I made - SJC
    emotion = emotion_to_vec(row['emotion'])
    imagePath = SAVE_DIRECTORY + row['image']
    img = Image.open(imagePath).convert("L")
    imgArray = np.array(img)
    labels.append(emotion)
    images.append(imgArray)
    index += 1
    print("Progress: {}/{} {:.2f}%".format(index, total, index * 100.0 / total))

print("Total: " + str(len(images)))
np.save('data_test.npy', images)
np.save('labels_test.npy', labels)