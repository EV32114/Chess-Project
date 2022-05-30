import cv2
import numpy as np
from skimage.filters import threshold_otsu
import crop
import socketlib
import arduino


class Chess:
    def __init__(self):
        self.boardMask = np.zeros((8, 8), dtype=bool)  # the mask of the board.
        self.chessBoard = np.array([["R", "N", "B", "Q", "K", "B", "N", "R"],
                                    ["P", "P", "P", "P", "P", "P", "P", "P"],
                                    ["", "", "", "", "", "", "", ""],
                                    ["", "", "", "", "", "", "", ""],
                                    ["", "", "", "", "", "", "", ""],
                                    ["", "", "", "", "", "", "", ""],
                                    ["p", "p", "p", "p", "p", "p", "p", "p"],
                                    ["r", "n", "b", "q", "k", "b", "n", "r"]])  # default chess board (before changes).
        self.averageColors = []
        self.updatedChess = np.zeros((8, 8))  # array consisting of 0's for now, will later be use to hold the
        # current chess board.
        self.sock = socketlib.connect()  # the socket used to communicate with the chess program.
        self.vid = cv2.VideoCapture(1)  # cropping the image to the desired
        # frame.
        self.ret, self.frame = self.vid.read()  # take a frame
        self.refPt = crop.crop_image(self.frame)


def round_down_to_next_multiple_of_8(a):
    """
    Round to next smaller multiple of 8
    https://www.geeksforgeeks.org/round-to-next-smaller-multiple-of-8/
    Explanation: the last three bits in the binary representation of a number will be 0.
    :param a: the number we round down.
    :return: the result.
    """
    return a & (-8)  # rounds down to the next multiple of 8 using the algorithm above.


def convert(x, y):
    """
    we convert the numbers to a proper chess position for printing.
    :param x: the file it is in.
    :param y: the rank it is in.
    :return: the string consisting of the position.
    """
    strY = chr(97 + y)
    returnStr = strY + str(8 - x)
    return returnStr


def resizeImage(img):
    """
    Read image, and shrink to quadratic shape with width and height of
    next smaller multiple of 8.
    Explanation img.shape[:2] holds the width and height of the image.
    We make the width and height into an array and round each down to the next
    multiple of 8. after that, we use np.min to get the minimum from the array 
    (as the picture should hypotethically be a square).
    :param img: the image we resize.
    :return: the resized image.
    """
    wh = np.min(round_down_to_next_multiple_of_8(np.array(img.shape[:2])))
    img = cv2.resize(img, (wh, wh))
    return img


# we prepare the visualization output.
# out = img.copy()
# plt.figure(1, figsize=(18, 6))
# plt.subplot(1, 3, 1), plt.imshow(img)

def blurImg(img):
    """
    blurs the image.
    :param img: the image we blur.
    :return: the blurred image.
    """
    img = cv2.blur(img, (5, 5))
    return img


def getUniqueColors(img):
    """
    we iterate over the tiles, and count the unique colors inside each tile.
    we use the following algorithm:
    https://stackoverflow.com/a/56606457/11089932
    :param img: the image we want to take the colors from.
    :return: an array consisting of the unique colors of each tiles, and the size of each tile.
    """
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


def getCenter(img):
    """
    We make an array consisting of the center pixels of each tile.
    :param img: the image we want to take the pixels from.
    :return: the array.
    """
    wh = np.min(round_down_to_next_multiple_of_8(np.array(img.shape[:2])))  # we find the size of the board.
    wh_t = wh // 8  # we find the size of each tile.
    centerPixel = []
    for i in range(8):
        centerPixel.append([0, 0, 0, 0, 0, 0, 0, 0])
    for x in np.arange(8):
        for y in np.arange(8):
            tile = img[y * wh_t:(y + 1) * wh_t, x * wh_t:(x + 1) * wh_t]
            tile = tile[3:-3, 3:-3]
            centerPixel[y][x] = tile[int(tile.shape[0] / 2), int(tile.shape[1] / 2)]
    return centerPixel


def threshAndMask(count_unique_colors):
    """
    we mask empty squares using cutoff from Otsu's method
    reference: https://en.wikipedia.org/wiki/Otsu%27s_method
    we can decrease the val to get more accurate results, however,
    this can only work granted we use pieces that don't match the dark board.
    therefore, we should most likely refrain from using this unless testing and seeing
    reliability.
    :param count_unique_colors: an array consisting of the unique color of each tile.
    :return: the mask of the frame.
    """
    val = threshold_otsu(count_unique_colors)  # a value used to distinguish between the foreground and the background.
    mask = count_unique_colors < val
    return mask


def mark(out, mask, wh_t):
    """
    In this function we mark every empty square.
    :param out: the frame on which we want to mark.
    :param mask: the mask.
    :param wh_t: the size of each tile.
    :return: Nothing.
    """
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.


def updateBoardAndMark(out, mask, wh_t, chess):
    """
    In this function we update our board and mark every empty square.
    1 signifies an empty space whilst 0 signifies a space that's taken.
    :param chess: instance of the class chess.
    :param out: the frame on which we want to mark.
    :param mask: the mask.
    :param wh_t: the size of each tile.
    :return: the marked frame.
    """
    for x in np.arange(8):
        for y in np.arange(8):
            if mask[y, x]:
                cv2.rectangle(out, (x * wh_t + 3, y * wh_t + 3),
                              ((x + 1) * wh_t - 3, (y + 1) * wh_t - 3), (255, 0, 0),
                              2)  # just for visuals, it surrounds the square.
                chess.updatedChess[y, x] = 1
            else:
                chess.updatedChess[y, x] = 0

    return out


# plt.subplot(1, 3, 2), plt.imshow(count_unique_colors, cmap='gray')
# plt.subplot(1, 3, 3), plt.imshow(out)
# plt.tight_layout(), plt.show()
# now, we have an array called updatedChess which holds the chess board.
# all we need to do now is compare the two arrays, and see which piece moved.

def get_move(chess):
    """
    We find the move the user made, print it to the screen and then return it to be sent to the chess program.
    :param chess: instance of the class chess.
    :return: the move the user made in the format: "RFRF" (R - Rank, F - File) for example: "e2e4".
    """
    string = ""
    data = ""
    break_flag = False
    pieceThatMoved = 0
    for x in np.arange(8):
        if break_flag:
            break
        for y in np.arange(8):
            if chess.updatedChess[x, y] == 1 and chess.chessBoard[x, y] != "":
                pieceThatMoved = chess.chessBoard[x, y]
                string = chess.chessBoard[x, y] + " Moved from " + convert(x, y)
                data += convert(x, y)
                chess.chessBoard[x, y] = ""
                break_flag = True
                break

    for x in np.arange(8):
        for y in np.arange(8):
            if chess.updatedChess[x, y] == 0 and chess.chessBoard[x, y] == "":
                string += " to position " + convert(x, y)
                chess.chessBoard[x, y] = pieceThatMoved
                data += convert(x, y)
                print(string)
                return data

    print(string)
    return data


def stabilizeMask(prevMasks):
    """
    We stabilize a mask using the list we made previous masks, and return the stabilized mask.
    :param prevMasks: a list of previous masks.
    :return: a stabilized mask.
    """
    mask = np.zeros((8, 8), dtype=bool)
    for mask1 in prevMasks:
        for mask2 in prevMasks:
            for x in np.arange(8):
                for y in np.arange(8):
                    if not (not mask1[x, y] and not mask2[x, y]):
                        mask[x, y] = True

    return mask


def compareMasks(mask1, mask2):
    """
    We compare the masks we got and return a stabilized mask.
    :param mask1: a mask.
    :param mask2: a mask.
    :return: the stabilized mask.
    """
    mask = np.zeros((8, 8), dtype=bool)
    for x in np.arange(8):
        for y in np.arange(8):
            if not (not mask1[x, y] and not mask2[x, y]):
                mask[x][y] = True

    return mask


def handle_data(data):
    """
    We handle the data received according to his value.
    :param data: the data we received.
    :return: the flag corresponding to the data given.
    """
    data = int(data)
    if data == 0:
        print('valid move')
        return 0
    if data == 1:
        # handle_check() TODO
        return 0
    if data == 8:
        # handle_mate() TODO
        return 3
    if data == 9:
        # handle_castle() TODO
        return 4
    else:
        handle_invalid()
        return -1


def getAverageColors(img):
    averageColor = []
    # we round the size of the image to the next multiple of 8
    wh = np.min(round_down_to_next_multiple_of_8(np.array(img.shape[:2])))
    wh_t = wh // 8  # we use floor division and thus find size of each tile. (wh_t x wh_t)

    for x in np.arange(8):
        for y in np.arange(8):
            tile = img[y * wh_t:(y + 1) * wh_t, x * wh_t:(x + 1) * wh_t]
            tile = tile[3:-3, 3:-3]
            average = tile.mean(axis=0).mean(axis=0)
            averageColor.append(average)
    return averageColor


def checkEating(chess, img):
    average = getAverageColors(img)

    for i, x in enumerate(range(64)):
        if abs(average[i][0] - chess.averageColors[i][0]) > 50 or abs(average[i][1] - chess.averageColors[i][1]) > 50 or abs(average[i][2] - chess.averageColors[i][2]) > 50:
            if not chess.boardMask[i % 8, i // 8]:
                print("Ate the piece at place " + convert(i % 8, i // 8))
                return True
    return False


def handle_invalid():
    """
    we handle invalid moves in this function.
    """
    print("Invalid move! Please make a legal move!")


def main():
    chess = Chess()
    flag = 0
    moved = False
    stabilized = False
    chess.vid.set(cv2.CAP_PROP_CONVERT_RGB, 1)  # we enhance the frame.
    prevMasks = []  # will be used to store previous masks (for stabilization).
    print(chess.refPt)
    centerTaken = False
    while flag != 8:

        ret_main, frame_main = chess.vid.read()  # we read the frame

        """
        we have previously discovered our reference points, these are the points
        we need to crop our image to in order to find the chessboard and get the best
        picture of it. As so, in this line we crop the image to get our desired frame.
        """
        frame_main = frame_main[chess.refPt[0][1]:chess.refPt[1][1], chess.refPt[0][0]:chess.refPt[1][0]]
        last_frame = frame_main
        if not centerTaken:
            """
            In case the center of each tile was not taken yet,
            we take it.
            """
            firstCenterArray = getCenter(frame_main)
            centerTaken = True

        frame_main = resizeImage(frame_main)  # we resize the image.

        first_frame = frame_main  # we use it to later on show a high quality image.
        frame_main = blurImg(frame_main)  # we blur the image.

        """
        we get an array, or, more accurately an image representation
        of the unique colors in the frame.
        """
        count_unique_colors, wh_t = getUniqueColors(frame_main)

        """
        we threshold using Otsu's method and 
        mask the received count of unique colors.
        """
        mask = threshAndMask(count_unique_colors)

        if not stabilized:
            """
            If the board is not stabilized yet, we continue the stabilizing process
            """
            prevMasks.append(mask)
            if len(prevMasks) == 20:
                chess.boardMask = stabilizeMask(prevMasks)
                stabilized = True
                chess.averageColors = getAverageColors(first_frame)

        if stabilized:
            """
            If the board is stabilized, we keep the mask the same until 'q' (timer button) is pressed.
            """
            # chess.boardMask = compareMasks(mask, chess.boardMask) - OPTIONAL
            mask = chess.boardMask

        mark(out=first_frame, mask=mask, wh_t=wh_t)  # we mark the frame.
        cv2.imshow('frame', first_frame)  # we display the frame after it's marked.
        # if port.in_waiting:
        #     data = arduino.get_input(port)
        #     moved = arduino.check_button_mode(data)

        key = cv2.waitKey(1) & 0xFF

        if moved or key == ord("q"):
            """
            this key click means the player had played his turn and we can scan the
            board. Therefore, we will now scan the board again, find the differences
            between the array of the start of the turn, and the aftermath, and display
            what we found the move was.
            """
            prevMasks = []
            backup_mask = chess.boardMask
            while len(prevMasks) != 10:
                ret_main, frame_main = chess.vid.read()
                frame_main = frame_main[chess.refPt[0][1]:chess.refPt[1][1], chess.refPt[0][0]:chess.refPt[1][0]]
                frame_main = resizeImage(frame_main)
                frame_main = blurImg(frame_main)
                count_unique_colors, wh_t = getUniqueColors(frame_main)
                mask = threshAndMask(count_unique_colors)
                prevMasks.append(mask)
            chess.boardMask = stabilizeMask(prevMasks)  # we create a stabilized mask using the masks we have found.
            if len(prevMasks) == 10:
                eating = checkEating(chess, frame_main)
                print(eating)
                prevMasks.append(mask)
            centerArray = getCenter(frame_main)  # we create an array of the center pixel of each tile.
            backup_board = chess.updatedChess  # we keep a backup board in case of an invalid move.
            backup_frame = frame_main  # we keep a backup frame in case of an invalid move.
            updateBoardAndMark(backup_frame, chess.boardMask, wh_t, chess)  # we update the board and mark the new empty
            # squares.
            data_to_send = get_move(chess)  # we get the move to send the chess program.
            socketlib.send_data(chess.sock, data_to_send)  # we send the data we got.
            ans = socketlib.recv_data(chess.sock)  # we receive the answer from the chess program.

            """
            we handle the answer received
            """
            flag = handle_data(ans)
            if flag == -1:
                # TODO handle check and shit
                pass

            cv2.imshow('frame', frame_main)  # we display the final frame.
            firstCenterArray = centerArray  # we update the center pixel array.
            # port.reset_input_buffer()  # we reset the input buffer
            moved = False
            chess.averageColors = getAverageColors(frame_main)

    cv2.waitKey(0)
    cv2.destroyAllWindows()



if __name__ == "__main__":
    main()
