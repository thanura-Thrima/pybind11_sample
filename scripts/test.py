import cv2
import numpy as np
import ApplicationLogic as appLogic

def test_func(i):
    print(i)
    app = appLogic.Application()
    app.get()
    for i in range(1,10):
        #img = app.getImage()
        print (len(app.image))

