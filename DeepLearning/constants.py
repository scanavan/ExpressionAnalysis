#                               __                    __             
#                              /\ \__                /\ \__          
#   ___    ___     ___     ____\ \ ,_\    __      ___\ \ ,_\   ____  
#  /'___\ / __`\ /' _ `\  /',__\\ \ \/  /'__`\  /' _ `\ \ \/  /',__\ 
# /\ \__//\ \L\ \/\ \/\ \/\__, `\\ \ \_/\ \L\.\_/\ \/\ \ \ \_/\__, `\
# \ \____\ \____/\ \_\ \_\/\____/ \ \__\ \__/.\_\ \_\ \_\ \__\/\____/
#  \/____/\/___/  \/_/\/_/\/___/   \/__/\/__/\/_/\/_/\/_/\/__/\/___/  .txt
#
#

CASC_PATH = './haarcascade_files/haarcascade_frontalface_default.xml'
SIZE_FACE = 48
EMOTIONS = ['angry', 'disgusted', 'fearful', 'happy', 'sad', 'surprised', 'neutral']
SAVE_DIRECTORY = './data/cropped/'
SAVE_MODEL_FILENAME = 'USF_TEST_MODEL_1Epoch'
SAVE_DATASET_IMAGES_FILENAME = 'data_train.npy'
SAVE_DATASET_LABELS_FILENAME = 'labels_train.npy'
SAVE_DATASET_IMAGES_TEST_FILENAME = 'data_test.npy'
SAVE_DATASET_LABELS_TEST_FILENAME = 'labels_test.npy'