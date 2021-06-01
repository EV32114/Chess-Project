import numpy as np
import cv2
import sys
import math
import glob
import scipy.spatial as spatial
import scipy.cluster as cluster
from collections import defaultdict
from statistics import mean
import chess
import chess.svg
import sys
import os

nline = 8 # number of lines (it's a chess board)
ncolumn = 8 # number of columns (it's a chess board)
img = cv2.imread('Chess.png') # we read the image
blur = cv2.GaussianBlur(img,(5,5),0) # we use the gaussian blur


gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
dst = cv2.Canny(gray, 50, 200)
lines= cv2.HoughLines(dst, 1, math.pi/180.0, 150, np.array([]), 0, 0)
a,b,c = lines.shape
for i in range(a):
    rho = lines[i][0][0]
    theta = lines[i][0][1]
    a = math.cos(theta)
    b = math.sin(theta)
    x0, y0 = a*rho, b*rho
    pt1 = (int(x0+1000*(-b)), int(y0+1000*(a)) )
    pt2 = (int(x0-1000*(-b)), int(y0-1000*(a)) )
    cv2.line(img, pt1, pt2, (0, 255, 0), 2, cv2.LINE_AA)
cv2.imshow('img', img)


#scale_percent = 50
# resize by 50%
#width = int(img.shape[1] * scale_percent / 100)
#height = int(img.shape[0] * scale_percent / 100)
# dsize
#dsize = (width, height)

# resize image
#output = cv2.resize(img, dsize)
output = img


sigma = 0.33
v = np.median(img) #finding something I'm not sure what
img = cv2.medianBlur(img, 5) # we use median blur on the image
img = cv2.GaussianBlur(img, (7, 7), 2) # we use gaussian blur on the image to make it clear.
lower = int(max(0, (1.0 - sigma) * v)) # we find the lower threshold.
upper = int(min(255, (1.0 + sigma) * v)) # we find the higher threshold.
img_edge = cv2.Canny(output, lower, upper) # we use the canny function to edge canny the image.
cv2.imshow('im cool', img_edge) # we show the image.


# resize by 50%
#width = int(img.shape[1] * scale_percent / 100)
#height = int(img.shape[0] * scale_percent / 100)

# dsize
#dsize = (width, height)

# resize image
#output = cv2.resize(img, dsize)

#use it if you ever find out how to make it work better
#imgSave = cv2.drawChessboardCorners(imgSave, (7, 7), corners, ret)


cv2.waitKey(0)
cv2.destroyAllWindows()
