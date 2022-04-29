#include <WiFi.h>
#include <Stepper.h>

#define SQUARE_STEPS 10 // TEMP -> CHANGE LATER
#define STEPS_PER_REVOLUTION 2048 // Steps per revolution.
#define SSID "ESP32-AP" // WiFi name.
#define PASSWORD "12345678" // WiFi password.

Stepper step1 = Stepper(STEPS_PER_REVOLUTION, 32, 25, 33, 26); // Creating an object of our stepper motor.
Stepper step2 = Stepper(STEPS_PER_REVOLUTION, 27, 13, 14, 12); // Creating an object of our stepper motor.

/*
 * Function Declarations
 */
void handleRequest(String userReq); 
void moveSteppers(int nNumOfSteps, char cDirection);
void moveUp(int nNumOfSteps);
void moveDown(int nNumOfSteps);
void moveLeft(int nNumOfSteps);
void moveRight(int nNumOfSteps);

WiFiServer wifiServer(1337);

void setup() {
  int notConnectedCounter = 0;
  Serial.begin(115200); // set the communication frequency to 115200Hz
  step1.setSpeed(10);
  step2.setSpeed(10); 
  delay(1000);
  WiFi.mode(WIFI_AP_STA); // set the Wi-Fi mode to Access Point
  if (!WiFi.softAP(SSID, PASSWORD)) // If we failed to initiate the Wi-Fi access point, we display an error.
  {
   Serial.println("Failed to init WiFi AP");
   return;
  }
  else // Else, we print the ip address
  {
   Serial.println("IP adress of AP is:");
   Serial.println(WiFi.softAPIP());
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin(); // we start the Wi-Fi server.
}

void loop() {
  /* 
   *  Variable and object initializations
   */
  WiFiClient client = wifiServer.available();   // Listen for incoming clients
  String userReq = "";
  
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client
        char charIn = client.read();        // read a byte, then
        userReq += charIn;                  // add it to the string.
        if(userReq.length() == 4){          // if we're done reading
          handleRequest(userReq);           // we send the data to be handled.
          userReq = "";                     // reset the data, and then
          client.write("OK");               // print a message that our job has been done.
        }

      }
    }
  }
}

/*
 * handles the request for moving, sends it to calculateMove.
 */
void handleRequest(String userReq){
  int src[] = {(int)userReq[0], (int)userReq[1]};
  int target[] = {(int)userReq[2], (int)userReq[3]};
  calculateMove(src, target);
}

/*
 * responsible for moving the magnet at the start and the end of the movement.
 * isUnder: is the target under the original magnet location.
 * isLeft: is the target to the left of the original magnet location.
*/
void moveStartAndEnd(bool isUnder, bool isLeft) {
  if(isUnder)
    moveUp(SQUARE_STEPS / 2);
  else
    moveDown(SQUARE_STEPS / 2);
  if(isLeft)
    moveRight(SQUARE_STEPS / 2);
  else
    moveLeft(SQUARE_STEPS / 2);
}

/*
 * calculate the distance required of the magnet to move and move it.
 * the movement is done in steps up/down and left/right between the squares such that the piece will not hit any other pieces.
 * src: the source location of the magnet.
 * target: the target square on the board.
*/
void calculateMove(int* src, int* target){
  // Getting the delta x and y coordinates.
  int dX = src[1] - target[1];
  int dY = src[0] - target[0];
  // Determining whether the point is under or is to the left of the target point.
  bool isUnder = dY < 0;
  bool isLeft = dX < 0;

  int currX = src[1];
  int currY = src[0];
  moveStartAndEnd(isUnder, isLeft);
  for(int i = 0; i < max(abs(dX) - 1, abs(dY)); i++){
    if (currX != target[1] - 1) {
      if(isLeft)
        moveRight(SQUARE_STEPS);
      else
        moveLeft(SQUARE_STEPS);
      currX += 1;
    }
    if(currY != target[0]){
      if(isUnder)
        moveUp(SQUARE_STEPS);
      else
        moveDown(SQUARE_STEPS);
     }
     currY += 1;
  }
  moveStartAndEnd(isUnder, isLeft);
}
\

/*
 * First of all, we shall decide on which stepper motor is responsible
 * for each movement.
 * Therefore, we shall decide this:
 * Stepper Motor 1 (step1): Up, Down
 * Stepper Motor 2 (step2): Right, Left
 */
void moveSteppers(int nNumOfSteps, char cDirection){
  switch(cDirection){
    case 'u':
      // We move up by given number of steps
      moveUp(nNumOfSteps);
      break;
      
    case 'd':
      // We move down by given number of steps
      moveDown(nNumOfSteps);
      break;

    case 'l':
      // We move left by given number of steps
      moveLeft(nNumOfSteps);
      break;
      
    case 'r':
      // We move right by given number of steps
      moveRight(nNumOfSteps);
      break;
  }
}

/*
 * Moves the magnet up
 */
void moveUp(int nNumOfSteps){
  step1.step(nNumOfSteps);  
}

/*
 * Moves the magnet down
 */
void moveDown(int nNumOfSteps){
  step1.step(-nNumOfSteps);  
}

/*
 * Moves the magnet left
 */
void moveLeft(int nNumOfSteps){
  step2.step(-nNumOfSteps);
}

/*
 * Moves the magnet right
 */
void moveRight(int nNumOfSteps){
  step2.step(nNumOfSteps);
}

/*
 * Moves the magnet diagonally up and right.
 */
void moveDiagonalUpRight(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps; i++){
      moveUp(1);
      moveRight(1);
  }  
}

/*
 * Moves the magnet diagonally down and right.
 */
void moveDiagonalDownRight(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps; i++){
      moveDown(1);
      moveRight(1);
  }  
}

/*
 * Moves the magnet diagonally down and left.
 */
void moveDiagonalDownLeft(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps; i++){
      moveDown(1);
      moveLeft(1);
  }  
}

/*
 * Moves the magnet diagonally up and left.
 */
void moveDiagonalUpLeft(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps; i++){
      moveUp(1);
      moveLeft(1);
  }  
}

void moveMotorsToIndex(int src1, int src2, int dest1, int dest2) {
  int row = src1 - src2;
  int col = src2 - dest2;
  while (abs(row) > 0 || abs(col) > 0) {
    if (row == 0) {
      moveLeft(0.5); // get out of the way of the other pieces
      if (col < 0) {
        moveDown(abs(col));
      }
      else {
        moveUp(abs(col));
      }
      moveRight(0.5); // move back to the center of the square
      return;
    }
    if (col == 0) {
      moveUp(0.5); // get out of the way of the other pieces
      if (row < 0) {
        moveLeft(abs(row));
      }
      else {
        moveRight(abs(row));
      }
      moveDown(0.5); // move back to the center of the square
      return;
    }
    if (row < 0 && col < 0) {
      moveDiagonalUpLeft(1);
      row++;
      col++;
    }
    else if (row < 0 && col > 0) {
      moveDiagonalUpRight(1);
      row++;
      col--;
    }
    else if (row > 0 && col < 0) {
      moveDiagonalDownLeft(1);
      row--;
      col++;
    }
    else if (row > 0 && col < 0) {
      moveDiagonalDownRight(1);
      row--;
      col--;
    }
  }
}
