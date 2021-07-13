# import the necessary packages
# import argparse
import cv2

# initialize the list of reference points and boolean indicating
# whether cropping is being performed or not
refPt = []
cropping = False

def click_and_crop(event, x, y, flags, param):
    # grab references to the global variables
    global refPt, cropping
    # if the left mouse button was clicked, record the starting
    # (x, y) coordinates and indicate that cropping is being
    # performed
    if event == cv2.EVENT_LBUTTONDOWN:
        refPt = [(x, y)]
        cropping = True
    # check to see if the left mouse button was released
    elif event == cv2.EVENT_LBUTTONUP:
        # record the ending (x, y) coordinates and indicate that
        # the cropping operation is finished
        refPt.append((x, y))
        cropping = False
        # draw a rectangle around the region of interest
        cv2.rectangle(param, refPt[0], refPt[1], (0, 255, 0), 2)


def crop_image(frame):
    image = frame
    clone = image.copy()
    cv2.namedWindow("image")
    cv2.setMouseCallback("image", click_and_crop, param=frame)

    # keep looping until the 'q' key is pressed
    while True:
        # display the image and wait for a keypress
        cv2.imshow("image", image)
        key = cv2.waitKey(1) & 0xFF

        # if the 'c' key is pressed, break from the loop
        if key == ord("c"):
            break
    # if there are two reference points, then crop the region of interest
    # from teh image and display it
    # if len(refPt) == 4:
    #     top_left_x = min(refPt[0][0], refPt[1][0], refPt[2][0], refPt[3][0])
    #     top_left_y = min(refPt[0][1], refPt[1][1], refPt[2][1], refPt[3][1])
    #     bot_right_x = max(refPt[0][0], refPt[1][0], refPt[2][0], refPt[3][0])
    #     bot_right_y = max(refPt[0][0], refPt[1][0], refPt[2][0], refPt[3][0])
    #     return [(top_left_x, top_left_y), (bot_right_x, bot_right_y)]
    if len(refPt) == 2:
        return refPt

    # close all open windows


cv2.destroyAllWindows()
