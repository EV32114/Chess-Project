#include <WiFi.h>
#include <Stepper.h>

#define SQUARE_STEPS 37
// #define STEPS_PER_REVOLUTION 2048 // Steps per revolution.
#define SSID "ESP32-AP" // WiFi name.
#define PASSWORD "12345678" // WiFi password.

#define PIN_TOP_A 26
#define PIN_TOP_B 12
#define PIN_TOP_C 14
#define PIN_TOP_D 27

#define PIN_MIDDLE_A 19
#define PIN_MIDDLE_B 23
#define PIN_MIDDLE_C 22
#define PIN_MIDDLE_D 21

#define ELECTROMAGNET_PIN 18
/*
 * Function Declarations
 */
void handleRequest(String userReq); 
void moveSteppers(int nNumOfSteps, char cDirection);
void moveUp(int nNumOfSteps);
void moveDown(int nNumOfSteps);
void moveLeft(int nNumOfSteps);
void moveRight(int nNumOfSteps);
void forward(int A, int B, int C, int D, int numOfSteps);

WiFiServer wifiServer(1337);

void setup() {
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);

  pinMode(18, OUTPUT);

  digitalWrite(ELECTROMAGNET_PIN, HIGH);
  
  //moveMotorsToIndex(0, 0, 7, 7);
  
  /*int notConnectedCounter = 0;
  Serial.begin(115200); // set the communication frequency to 115200Hz
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
 
  wifiServer.begin(); // we start the Wi-Fi server.*/
  
}

void loop() {
  forward(19, 23, 22, 21, 100); // TEMP WORKING
  //delay(1000);
  //forward(26, 12, 14, 27, 100); // WORKING
  delay(1000);
  forward(19, 23, 22, 21, -100); // WORKING
  delay(1000);
  //forward(26, 12, 14, 27, -100); // WORKING
  //delay(1000);
  /* 
   *  Variable and object initializations
   */
  /*WiFiClient client = wifiServer.available();   // Listen for incoming clients
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
  }*/
}

/*
 * handles the request for moving, sends it to calculateMove.
 */
void handleRequest(String userReq){
  int src[] = {(int)userReq[0], (int)userReq[1]};
  int target[] = {(int)userReq[2], (int)userReq[3]};
  moveMotorsToIndex(src[0], src[1], target[0], target[1]);
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
  forward(PIN_TOP_A, PIN_TOP_B, PIN_TOP_C, PIN_TOP_D, nNumOfSteps);
}

/*
 * Moves the magnet down
 */
void moveDown(int nNumOfSteps){
  forward(PIN_TOP_A, PIN_TOP_B, PIN_TOP_C, PIN_TOP_D, -nNumOfSteps);
}

/*
 * Moves the magnet left
 */
void moveLeft(int nNumOfSteps){
  forward(PIN_MIDDLE_A, PIN_MIDDLE_B, PIN_MIDDLE_C, PIN_MIDDLE_D, -nNumOfSteps);
}

/*
 * Moves the magnet right
 */
void moveRight(int nNumOfSteps){
  forward(PIN_MIDDLE_A, PIN_MIDDLE_B, PIN_MIDDLE_C, PIN_MIDDLE_D, nNumOfSteps);
}

/*
 * Moves the magnet diagonally up and right.
 */
void moveDiagonalUpRight(int nNumOfSteps){
  moveUp(nNumOfSteps);
  moveRight(nNumOfSteps);  
}

/*
 * Moves the magnet diagonally down and right.
 */
void moveDiagonalDownRight(int nNumOfSteps){
  moveDown(nNumOfSteps);
  moveRight(nNumOfSteps);
}

/*
 * Moves the magnet diagonally down and left.
 */
void moveDiagonalDownLeft(int nNumOfSteps){
  moveDown(nNumOfSteps);
  moveLeft(nNumOfSteps); 
}

/*
 * Moves the magnet diagonally up and left.
 */
void moveDiagonalUpLeft(int nNumOfSteps){
  moveUp(nNumOfSteps);
  moveLeft(nNumOfSteps);
}

void moveMotorsToIndex(int src1, int src2, int dest1, int dest2) {
  int row = src1 - dest1; // 0 - 1 = -1
  int col = src2 - dest2; // 1 - 2 = -1
  digitalWrite(ELECTROMAGNET_PIN, HIGH);
  while (abs(row) > 0 || abs(col) > 0) {
    if (row == 0) {
      moveLeft(0.5 * SQUARE_STEPS); // get out of the way of the other pieces
      delay(500);
      if (col < 0) {
        moveDown(abs(col) * SQUARE_STEPS);
        delay(500);
      }
      else {
        moveUp(abs(col) * SQUARE_STEPS);
        delay(500);
      }
      moveRight(0.5 * SQUARE_STEPS); // move back to the center of the square
      delay(500);
      digitalWrite(ELECTROMAGNET_PIN, LOW);
      return;
    }
    if (col == 0) {
      moveUp(0.5 * SQUARE_STEPS); // get out of the way of the other pieces
      delay(500);
      if (row < 0) {
        moveLeft(abs(row) * SQUARE_STEPS);
        delay(500);
      }
      else {
        moveRight(abs(row) * SQUARE_STEPS);
        delay(500);
      }
      moveDown(0.5 * SQUARE_STEPS); // move back to the center of the square
      delay(500);
      digitalWrite(ELECTROMAGNET_PIN, LOW);
      return;
    }
    if (row < 0 && col < 0) {
      moveDiagonalDownLeft(SQUARE_STEPS);
      delay(500);
      row++;
      col++;
    }
    else if (row < 0 && col > 0) {
      moveDiagonalUpLeft(SQUARE_STEPS);
      
      delay(500);
      row++;
      col--;
    }
    else if (row > 0 && col > 0) {
      moveDiagonalUpRight(SQUARE_STEPS);
      delay(500);
      row--;
      col++;
    }
    else if (row > 0 && col < 0) {
      moveDiagonalDownRight(SQUARE_STEPS);
      delay(500);
      row--;
      col--;
    }
  }
}

void forward(int A, int B, int C, int D, int numOfSteps){
  if (numOfSteps > 0) {
   for(int i = 0; i < numOfSteps; i++){
    // 5
    digitalWrite(A, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    delay(2);
   
    // 6
    digitalWrite(A, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    delay(2);

    // 10
    digitalWrite(A, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    delay(2);
    // 9
    digitalWrite(A, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    if (A == PIN_TOP_A)
      delay(10);
    else
      delay(18);
   }
  }
   else if (numOfSteps < 0) {
    numOfSteps = numOfSteps * -1;
    for(int i = 0; i < numOfSteps; i++){
      // 9
      digitalWrite(A, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      delay(2);
  
      
      // 10
      digitalWrite(A, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      delay(2);
  
      // 6
      digitalWrite(A, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      delay(2);
      // 5
      digitalWrite(A, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      if (A == PIN_TOP_A)
        delay(10);
      else
        delay(18);
   } // 9 10 6 5
  }
}
