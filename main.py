import numpy as np
import cv2

import matplotlib.pyplot as plt
import numpy as np
from skimage.filters import threshold_otsu


img = cv2.imread('C:/Users/User/Downloads/twomove.png') # we read the image

# Round to next smaller multiple of 8
# https://www.geeksforgeeks.org/round-to-next-smaller-multiple-of-8/
def round_down_to_next_multiple_of_8(a):
    return a & (-8) # rounds down to the next multiple of 8 using the algorithm above.

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
chessBoard = np.array([["R", "N", "B", "K", "Q", "B", "N", "R"],
                      ["P", "P", "P", "P", "P", "P", "P", "P"],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["", "", "", "", "", "", "", ""],
                      ["p", "p", "p", "p", "p", "p", "p", "p"],
                      ["r", "n", "b", "q", "k", "b", "n", "r"]])

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
            print(chessBoard[x,y] + " Moved")
            chessBoard[x, y] = ""

for x in np.arange(8):
    for y in np.arange(8):
        if updatedChess[x, y] == 0 and chessBoard[x, y] == "":
            print("To Position: " + str(x) + " " + str(y))
            chessBoard[x,y] = pieceThatMoved

cv2.waitKey(0)
cv2.destroyAllWindows()
