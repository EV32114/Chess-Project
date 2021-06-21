import cv2
import matplotlib.pyplot as plt
import numpy as np
from skimage.filters import threshold_otsu
import crop

# default chess board (before changes).
chessBoard = np.array([["R", "N", "B", "Q", "K", "B", "N", "R"],
                       ["P", "P", "P", "P", "P", "P", "P", "P"],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["p", "p", "p", "p", "p", "p", "p", "p"],
                       ["r", "n", "b", "q", "k", "b", "n", "r"]])
# array converying the empty spaces.
updatedChess = np.zeros((8, 8))

vid = cv2.VideoCapture(r'Valorant_2021.06.12_-_12.20.20.01.mp4')
#vid = cv2.VideoCapture(0)
# take a frame
ret, frame = vid.read()
clone = frame.copy()
refPt = crop.poggers(frame)


# gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
# gray = np.float32(gray)
# dst = cv2.cornerHarris(gray, 2, 3, 0.04)
# result is dilated for marking the corners, not important
# dst = cv2.dilate(dst, None)
# # Threshold for an optimal value, it may vary depending on the image.
# frame[dst > 0.01 * dst.max()] = [0, 0, 255]
# cv2.imshow('dst', frame)
# img = cv2.imread('yes.jpg') # we read the image

# Round to next smaller multiple of 8
# https://www.geeksforgeeks.org/round-to-next-smaller-multiple-of-8/
def round_down_to_next_multiple_of_8(a):
    return a & (-8)  # rounds down to the next multiple of 8 using the algorithm above.


# we convert the numbers to a proper chess position for printing.
def convert(x, y):
    strY = chr(97 + y)
    returnStr = strY + str(8 - x)
    return returnStr


# Read image, and shrink to quadratic shape with width and height of
# next smaller multiple of 8
def resizeImage(img):
    wh = np.min(round_down_to_next_multiple_of_8(
        np.array(img.shape[:2])))  # we round the size of the image to the next multiple of 8
    img = cv2.resize(img, (wh, wh))
    return img


# we prepare the visualization output.
# out = img.copy()
# plt.figure(1, figsize=(18, 6))
# plt.subplot(1, 3, 1), plt.imshow(img)

def blurImg(img):
    # we blur the image.
    img = cv2.blur(img, (5, 5))
    return img


# we iterate over the tiles, and count unique colors inside
# we use the following algorithm:
# https://stackoverflow.com/a/56606457/11089932
def getUniqueColors(img):
    wh = np.min(round_down_to_next_multiple_of_8(
        np.array(img.shape[:2])))  # we round the size of the image to the next multiple of 8
    wh_t = wh // 8
    count_unique_colors = np.zeros((8, 8))
    for x in np.arange(8):
        for y in np.arange(8):
            tile = img[y * wh_t:(y + 1) * wh_t, x * wh_t:(x + 1) * wh_t]
            tile = tile[3:-3, 3:-3]
            count_unique_colors[y, x] = np.unique(tile.reshape(-1, tile.shape[-1]), axis=0).shape[0]
    return count_unique_colors, wh_t


# we iterate over the tiles, and get the center pixel of each tile.
def getCenter(img):
    wh = np.min(round_down_to_next_multiple_of_8(
        np.array(img.shape[:2])))  # we round the size of the image to the next multiple of 8
    wh_t = wh // 8
    average_colors = np.zeros((8, 8))
    centerPixel = []
    for i in range(8):
        centerPixel.append([0, 0, 0, 0, 0, 0, 0, 0])
    for x in np.arange(8):
        for y in np.arange(8):
            tile = img[y * wh_t:(y + 1) * wh_t, x * wh_t:(x + 1) * wh_t]
            tile = tile[3:-3, 3:-3]
            centerPixel[y][x] = tile[int(tile.shape[0] / 2), int(tile.shape[1] / 2)]
    return centerPixel


# we mask empty squares using cutoff from Otsu's method
# reference: https://en.wikipedia.org/wiki/Otsu%27s_method
def threshAndMask(count_unique_colors):
    # we can decrease the val to get more accurate results, however, 
    # this can only work granted we use pieces that don't match the dark board.
    # therefore, we should most likely refrain from using this unless testing and seeing
    # reliability.
    val = threshold_otsu(count_unique_colors)
    mask = count_unique_colors < val
    return mask

def stabilizeMask(mask):
    board1 = getStatus()
    board2 = getStatus()
    board3 = getStatus()
    board4 = getStatus()
    board5 = getStatus()
    board6 = getStatus()
    board7 = getStatus()
    board8 = getStatus()
    board9 = getStatus()
    board10 = getStatus()
    checkBoards = [board1, board2, board3, board4, board5, board6, board7, board8, board9, board10]

    for x in np.arange(8):
        for y in np.arange(8):
            if not mask[y,x]:
                for board in checkBoards:
                    for board1 in checkBoards:
                        if board[y,x] != board1[y,x]:
                            mask[y,x] = not mask[y,x]
    return mask

            
# we mark every empty square.
def mark(out, mask, wh_t):
    mask = stabilizeMask(mask)
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.

def getStatus():
    ret, frame = vid.read()
    # we have previously discovered our reference points, these are the points 
    # we need to crop our image to in order to find the chessboard and get the best
    # picture of it. As so, in this line we crop the image to our desired area.
    frame = frame[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
    # we resize and blur the image.
    frame = resizeImage(frame)
    frame = blurImg(frame)
    # we get an array, or, more accurately an image representation of the unique
    # colors in the frame. 
    count_unique_colors, wh_t = getUniqueColors(frame)
    # we threshold using Otsu's method and mask the recieved count of unique colors.
    mask = threshAndMask(count_unique_colors)
    currentBoard = np.zeros((8, 8))
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y,x]:
                currentBoard[y,x] = 1
    return currentBoard

                
# we update the board and mark every empty square.
def updateBoardAndMark(out, mask, wh_t):
    # we put more visualization output, although we can already find the empty tiles.
    # however, in this function we also update our chess board using 0`s and 1`s where 
    # 1 signifies an empty space while 0 signifies a space that's taken.
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.
                updatedChess[y, x] = 1
            else:
                updatedChess[y,x] = 0

            print(updatedChess[y, x])
    return out


# plt.subplot(1, 3, 2), plt.imshow(count_unique_colors, cmap='gray')
# plt.subplot(1, 3, 3), plt.imshow(out)
# plt.tight_layout(), plt.show()
# now, we have an array called updatedChess which holds the chess board.
# all we need to do now is compare the two arrays, and see which piece moved.

def printMove(oldCenterArray, newCenterArray):
    global updatedChess
    global chessBoard
    string = ""
    pieceThatMoved = 0
    for x in np.arange(8):
        for y in np.arange(8):
            if updatedChess[x, y] == 1 and chessBoard[x, y] != "":
                pieceThatMoved = chessBoard[x, y]
                string = chessBoard[x, y] + " Moved from " + convert(x, y)
                chessBoard[x, y] = ""
                break

    for x in np.arange(8):
        for y in np.arange(8):
            if updatedChess[x, y] == 0 and chessBoard[x, y] == "":
                string += " to position " + convert(x, y)
                chessBoard[x, y] = pieceThatMoved
                print(string)
                return

    if 20 > len(string) > 5:
        for i, j in range(zip(len(oldCenterArray), len(newCenterArray))):
            for oldPos, newPos in zip(oldCenterArray[i], newCenterArray[j]):
                if oldPos[0] not in range(newPos[0] - 50, newPos[0] + 50):
                    string += " and ate " + chessBoard[i][j] + " at position " + convert(i,j)
                    print(string)


    print(string)


def test():
    # this while true will eventually have a breakpoint, it will break when
    # the game is over.
    frame = cv2.imread('chess.png')
    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # refPt = crop.poggers(frame)
    # we have previously discovered our reference points, these are the points
    # we need to crop our image to in order to find the chessboard and get the best
    # picture of it. As so, in this line we crop the image to our desired area.
    # frame = frame[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
    # we resize and blur the image.
    frame = resizeImage(frame)
    out = frame.copy()
    plt.figure(1, figsize=(18, 6))
    plt.subplot(1, 3, 1), plt.imshow(frame)
    frame = blurImg(frame)
    # we get an array, or, more accurately an image representation of the unique
    # colors in the frame.
    count_unique_colors, wh_t = getUniqueColors(frame)
    centerArray = getCenter(frame)
    plt.subplot(1, 3, 2), plt.imshow(count_unique_colors, cmap='gray')
    plt.tight_layout(), plt.show()
    # we threshold using Otsu's method and mask the recieved count of unique colors.
    mask = threshAndMask(count_unique_colors)
    mark(frame, mask, wh_t)
    cv2.imshow('frame', frame)
    printMove(centerArray, centerArray)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


def main():
    vid = cv2.VideoCapture(r'Valorant_2021.06.12_-_12.20.20.01.mp4')
    #vid = cv2.VideoCapture(0) # we turn on the camera.
    vid.set(cv2.CAP_PROP_CONVERT_RGB, 1)
    centerTaken = False
    while True:
        # this while true will eventually have a breakpoint, it will break when
        # the game is over.
        ret, frame = vid.read()
        # we have previously discovered our reference points, these are the points 
        # we need to crop our image to in order to find the chessboard and get the best
        # picture of it. As so, in this line we crop the image to our desired area.
        frame = frame[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
        if not centerTaken:
            firstCenterArray = getCenter(frame)
            centerTaken = True
        # we resize and blur the image.
        frame = resizeImage(frame)
        frame = blurImg(frame)
        # we get an array, or, more accurately an image representation of the unique
        # colors in the frame. 
        count_unique_colors, wh_t = getUniqueColors(frame)
        # we threshold using Otsu's method and mask the recieved count of unique colors.
        mask = threshAndMask(count_unique_colors)

        mark(frame, mask, wh_t)
        cv2.imshow('frame', frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            # this key click means the player had played his turn and we can scan the
            # board. Therefore, we will now scan the board again, find the differences
            # between the array of the start of the turn, and the aftermath, and display
            # what we found the move was. 
            ret, frame = vid.read()
            frame = frame[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
            frame = resizeImage(frame)
            frame = blurImg(frame)
            count_unique_colors, wh_t = getUniqueColors(frame)
            mask = threshAndMask(count_unique_colors)
            # and we update the board and mark the free spaces.
            centerArray = getCenter(frame)
            updateBoardAndMark(frame, mask, wh_t)
            # we show the frame we got.
            cv2.imshow('frame', frame)
            # we print the final move.
            printMove(firstCenterArray, centerArray)
            firstCenterArray = centerArray

    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
