import numpy as np
import cv2
import matplotlib.pyplot as plt
import numpy as np
from skimage.filters import threshold_otsu
# we create the before-change chessboard.
import crop
chessBoard = np.array([["R", "N", "B", "K", "Q", "B", "N", "R"],
                      ["P", "P", "P", "P", "P", "P", "P", "P"],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["p", "p", "p", "p", "p", "p", "p", "p"],
                      ["r", "n", "b", "q", "k", "b", "n", "r"]])

vid = cv2.VideoCapture(0)

# take a frame
ret, frame = vid.read()
clone = frame.copy()
refPt = crop.poggers(frame)
print(refPt)
# Display the resulting frame
vid = cv2.VideoCapture(0)

while True:
    ret, frame = vid.read()
    frame = frame[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
    cv2.imshow('frame', frame)
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break


scale_percent = 20  # percent of original size
width = int(frame.shape[1] * scale_percent / 100)
height = int(frame.shape[0] * scale_percent / 100)
dim = (width, height)

# resize image
frame = cv2.resize(frame, dim, interpolation=cv2.INTER_AREA)
# img = cv2.imread('yes.jpg') # we read the image

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret, corners = cv2.findChessboardCorners(gray, (8,8), cv2.CALIB_CB_ADAPTIVE_THRESH)
print(ret)
# Round to next smaller multiple of 8
# https://www.geeksforgeeks.org/round-to-next-smaller-multiple-of-8/
def round_down_to_next_multiple_of_8(a):
    return a & (-8) # rounds down to the next multiple of 8 using the algorithm above.

# we convert the numbers to a proper chess position
def convert(x, y):
    strY = chr(97 + y)
    returnStr = strY + str(8-x)
    return returnStr

# Read image, and shrink to quadratic shape with width and height of
# next smaller multiple of 8
wh = np.min(round_down_to_next_multiple_of_8(np.array(img.shape[:2]))) # we round the size of the image to the next multiple of 8
img = cv2.resize(img, (wh, wh))

# we prepare the visualization output.
out = img.copy()
plt.figure(1, figsize=(18, 6))
plt.subplot(1, 3, 1), plt.imshow(img)

# we blur the image.
img = cv2.blur(img, (5, 5))

# we iterate over the tiles, and count unique colors inside
# we use the following algorithm:
# https://stackoverflow.com/a/56606457/11089932
wh_t = wh // 8
count_unique_colors = np.zeros((8, 8))
for x in np.arange(8):
    for y in np.arange(8):
        tile = img[y*wh_t:(y+1)*wh_t, x*wh_t:(x+1)*wh_t]
        tile = tile[3:-3, 3:-3]
        count_unique_colors[y, x] = np.unique(tile.reshape(-1, tile.shape[-1]), axis=0).shape[0]

# we mask empty squares using cutoff from Otsu's method
# reference: https://en.wikipedia.org/wiki/Otsu%27s_method
val = threshold_otsu(count_unique_colors)
mask = count_unique_colors < val


updatedChess = np.zeros((8,8))
# we put more visualization output, although we can already find the empty tiles.
for x in np.arange(8):
    for y in np.arange(8):
        if mask[y, x]:
            cv2.rectangle(out, (x*wh_t+3, y*wh_t+3),
                          ((x+1)*wh_t-3, (y+1)*wh_t-3), (255, 0, 0), 2) # just for visuals, it surrounds the square.
            updatedChess[y, x] = 1

        print(updatedChess[y,x])

plt.subplot(1, 3, 2), plt.imshow(count_unique_colors, cmap='gray')
plt.subplot(1, 3, 3), plt.imshow(out)
plt.tight_layout(), plt.show()
# now, we have an array called updatedChess which holds the chess board.
# all we need to do now is compare the two arrays, and see which piece moved.
for x in np.arange(8):
    for y in np.arange(8):
        if updatedChess[x, y] == 1 and chessBoard[x, y] != "":
            pieceThatMoved = chessBoard[x, y]
            string = chessBoard[x,y] + " Moved from " + convert(x, y)
            chessBoard[x, y] = ""

for x in np.arange(8):
    for y in np.arange(8):
        if updatedChess[x, y] == 0 and chessBoard[x, y] == "":
            string += " to position " + convert(x, y)
            chessBoard[x,y] = pieceThatMoved

print(string)

cv2.waitKey(0)
cv2.destroyAllWindows()


