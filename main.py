import cv2
import numpy as np
from skimage.filters import threshold_otsu
import crop

boardMask = np.zeros((8, 8), dtype=bool)
# default chess board (before changes).
chessBoard = np.array([["R", "N", "B", "Q", "K", "B", "N", "R"],
                       ["P", "P", "P", "P", "P", "P", "P", "P"],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["", "", "", "", "", "", "", ""],
                       ["p", "p", "p", "p", "p", "p", "p", "p"],
                       ["r", "n", "b", "q", "k", "b", "n", "r"]])

# array conveying the empty spaces.
updatedChess = np.zeros((8, 8))

vid = cv2.VideoCapture(r'Valorant_2021.06.12_-_12.20.20.01.mp4')
# vid = cv2.VideoCapture(0)
# take a frame
ret, frame = vid.read()
clone = frame.copy()
refPt = crop.poggers(frame)


# Round to next smaller multiple of 8
# https://www.geeksforgeeks.org/round-to-next-smaller-multiple-of-8/
# Explanation: the last three bits in the binary representation of a number will be 0.
def round_down_to_next_multiple_of_8(a):
    return a & (-8)  # rounds down to the next multiple of 8 using the algorithm above.


def convert(x, y):
    """
    we convert the numbers to a proper chess position for printing.
    """
    strY = chr(97 + y)
    returnStr = strY + str(8 - x)
    return returnStr


def resizeImage(img):
    """
    Read image, and shrink to quadratic shape with width and height of
    next smaller multiple of 8
    Explanation img.shape[:2] holds the width and height of the image.
    We make the width and height into an array and round each down to the next
    multiple of 8. after that, we use np.min to get the minimum from the array 
    (as the picture should hypotethically be a square).
    """
    wh = np.min(round_down_to_next_multiple_of_8(
        np.array(img.shape[:2])))  # we round the size of the image to the next multiple of 8
    img = cv2.resize(img, (wh, wh))
    return img


# we prepare the visualization output.
# out = img.copy()
# plt.figure(1, figsize=(18, 6))
# plt.subplot(1, 3, 1), plt.imshow(img)

def blurImg(img):
    """
    blurs the image.
    """
    img = cv2.blur(img, (5, 5))
    return img


# we iterate over the tiles, and count unique colors inside
# we use the following algorithm:
# https://stackoverflow.com/a/56606457/11089932
def getUniqueColors(img):
    wh = np.min(round_down_to_next_multiple_of_8(
        np.array(img.shape[:2])))  # we round the size of the image to the next multiple of 8
    wh_t = wh // 8  # we use floor division and thus find size of each tile. (wh_t x wh_t)
    count_unique_colors = np.zeros((8, 8))
    for x in np.arange(8):
        for y in np.arange(8):
            tile = img[y * wh_t:(y + 1) * wh_t, x * wh_t:(x + 1) * wh_t]
            tile = tile[3:-3, 3:-3]
            count_unique_colors[y, x] = np.unique(tile.reshape(-1, tile.shape[-1]), axis=0).shape[0]
    return count_unique_colors, wh_t


# we iterate over the tiles, and get the center pixel of each tile.


def getCenter(img):
    # we round the size of the image to the next multiple of 8
    wh = np.min(round_down_to_next_multiple_of_8(np.array(img.shape[:2])))
    wh_t = wh // 8
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


# we mark every empty square.
def markWithBoard(out, board, wh_t):
    for x in np.arange(8):
        for y in np.arange(8):
            if board[y, x] == 1:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.


# we mark every empty square.
def mark(out, mask, wh_t):
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.


def updatedChessboard(prevBoards):
    global updatedChess
    for x in np.arange(8):
        for y in np.arange(8):
            for board in prevBoards:
                for board2 in prevBoards:
                    if board[y, x] != board2[y, x]:
                        updatedChess[y, x] = 1
                    else:
                        if board[y, x] == 1:
                            board[y, x] = 1
                        board[y, x] = 0


def getUpdatedBoard(mask):
    # we put more visualization output, although we can already find the empty tiles.
    # however, in this function we also update our chess board using 0`s and 1`s where 
    # 1 signifies an empty space while 0 signifies a space that's taken.
    updatedBoard = np.zeros((8, 8))
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                updatedBoard[y, x] = 1
            else:
                updatedBoard[y, x] = 0
    return updatedBoard


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
                updatedChess[y, x] = 0

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
        for i in range(len(oldCenterArray)):
            for j in range(len(newCenterArray)):
                for oldPos in oldCenterArray[i]:
                    for newPos in newCenterArray[j]:
                        if oldPos[0] not in range(newPos[0] - 50, newPos[0] + 50):
                            string += " and ate " + chessBoard[i][j] + " at position " + convert(i, j)

    print(string)


def stabilizeMask(prevMasks):
    mask = np.zeros((8, 8), dtype=bool)
    for mask1 in prevMasks:
        for mask2 in prevMasks:
            for x in np.arange(8):
                for y in np.arange(8):
                    if (mask1[x, y] and not mask2[x, y]) or (not mask1[x, y] and mask2[x, y]) or (
                            mask2[x, y] and mask1[x, y]):
                        mask[x, y] = True
                    else:
                        if not mask[x, y]:
                            mask[x, y] = False
    return mask


def compareMasks(mask1, mask2):
    mask = np.zeros((8, 8), dtype=bool)
    for x in np.arange(8):
        for y in np.arange(8):
            if mask1[x, y] == True and mask2[x, y] == False or mask1[x, y] == False and mask2[x, y] == True or mask2[x, y] == True and mask1[x, y] == True:
                mask[x][y] = True
            else:
                if not mask[x][y]:
                    mask[x][y] = False
    return mask


def main():
    global boardMask
    prevBoard = []
    stabilized = False
    vid_main = cv2.VideoCapture(r'Valorant_2021.06.12_-_12.20.20.01.mp4')
    # vid = cv2.VideoCapture(0) # we turn on the camera.
    vid_main.set(cv2.CAP_PROP_CONVERT_RGB, 1)
    prevMasks = []
    centerTaken = False
    while True:  # this while true will eventually have a breakpoint, it will break when the game is over.
        ret_main, frame_main = vid_main.read()
        # we have previously discovered our reference points, these are the points
        # we need to crop our image to in order to find the chessboard and get the best
        # picture of it. As so, in this line we crop the image to our desired area.
        frame_main = frame_main[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
        if not centerTaken:
            firstCenterArray = getCenter(frame_main)
            centerTaken = True
        # we resize and blur the image.
        frame_main = resizeImage(frame_main)
        first_frame = frame_main  # will be used to show a good quality image.
        frame_main = blurImg(frame_main)
        # we get an array, or, more accurately an image representation of the unique
        # colors in the frame.
        count_unique_colors, wh_t = getUniqueColors(frame_main)
        # we threshold using Otsu's method and mask the recieved count of unique colors.
        mask = threshAndMask(count_unique_colors)
        if not stabilized:
            prevMasks.append(mask)
            if len(prevMasks) == 20:
                boardMask = stabilizeMask(prevMasks)
                stabilized = not stabilized
        if stabilized:
            boardMask = compareMasks(mask, boardMask)
            mask = boardMask
        mark(out=first_frame, mask=mask, wh_t=wh_t)
        cv2.imshow('frame', first_frame)

        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            prevMasks = []

            # this key click means the player had played his turn and we can scan the
            # board. Therefore, we will now scan the board again, find the differences
            # between the array of the start of the turn, and the aftermath, and display
            # what we found the move was.
            prevMasks = []
            while len(prevMasks) != 10:
                ret_main, frame_main = vid_main.read()
                frame_main = frame_main[refPt[0][1]:refPt[1][1], refPt[0][0]:refPt[1][0]]
                frame_main = resizeImage(frame_main)
                frame_main = blurImg(frame_main)
                count_unique_colors, wh_t = getUniqueColors(frame_main)
                mask = threshAndMask(count_unique_colors)
                prevMasks.append(mask)

            boardMask = stabilizeMask(prevMasks)  # replace with mask if needed
            # and we update the board and mark the free spaces.
            centerArray = getCenter(frame_main)
            updateBoardAndMark(frame_main, boardMask, wh_t)  # replace with mask if needed
            # we show the frame we got.
            cv2.imshow('frame', frame_main)
            # we print the final move.
            printMove(firstCenterArray, centerArray)
            firstCenterArray = centerArray

    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
