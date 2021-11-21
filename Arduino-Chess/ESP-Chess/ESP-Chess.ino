#include <WiFi.h>
#include <Stepper.h>


const int stepsPerRevolution = 2048;
const int stepsBetweenSquares = 400;
Stepper step1 = Stepper(stepsPerRevolution, 32, 25, 33, 26);
Stepper step2 = Stepper(stepsPerRevolution, 27, 13, 14, 12);

void handleRequest(String userReq);
void moveSteppers(int nNumOfSteps, char cDirection);

char* ssid = "ESP32-AP";
char* password = "12345678";
String userReq = "";

WiFiServer wifiServer(1337);

void setup() {
  int notConnectedCounter = 0;
  Serial.begin(115200);
  step1.setSpeed(10);
  step2.setSpeed(10);
  delay(1000);
  WiFi.mode(WIFI_AP_STA);
  if (!WiFi.softAP(ssid, password))
  {
   Serial.println("Failed to init WiFi AP");
  }
  else
  {
   Serial.println("IP adress of AP is:");
   Serial.println(WiFi.softAPIP());
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client
        char charIn = client.read();             // read a byte, then
        userReq += charIn;
        if(userReq.length() == 6){
          handleRequest(userReq);
          userReq = "";
          client.write("OK");
        }

      }
    }
  }
}

void handleRequest(String userReq){
  String sNumStr = "";
  char cDirection = ' ';
  int nNumOfSteps;
  for(int i = 0; i < 5; i++){
    sNumStr += userReq[i];
  }
  nNumOfSteps = sNumStr.toInt();
  cDirection = userReq[5];
  moveSteppers(nNumOfSteps, cDirection);
}

void calculateMove(int[] src, int[] target){
  // Getting the delta x and y coordinates.
  int dX = src[1] - target[1];
  int dY = src[0] - target[0];
  // Determining whether the point is under or is to the left of the target point.
  bool isUnder = dY < 0;
  bool isLeft = dX < 0;

  int currX = src[1];
  int currY = src[0];

  for(int i = 0; i < max(abs(dX) - 1, abs(dY)); i++){
      
  }

  if(isLeft)
    moveRight(SQUARE_STEPS / 2);
   else
    moveLeft(SQUARE_STEPS / 2);
}

void moveSteppers(int nNumOfSteps, char cDirection){
  /*
   * First of all, we shall decide on which stepper motor is responsible
   * for each movement.
   * Therefore, we shall decide this:
   * Stepper Motor 1 (step1): Up, Down
   * Stepper Motor 2 (step2): Right, Left
   */
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

void moveUp(int nNumOfSteps){
  step1.move(nNumOfSteps);  
}

void moveDown(int nNumOfSteps){
  step1.move(-nNumOfSteps);  
}

void moveLeft(int nNumOfSteps){
  step2.move(-nNumOfSteps);
}

void moveRight(int nNumOfSteps){
  step2.move(nNumOfSteps);
}

void moveDiagonalUpRight(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps){
      moveUp(1);
      moveRight(1);
  }  
}

void moveDiagonalDownRight(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps){
      moveDown(1);
      moveRight(1);
  }  
}

void moveDiagonalDownLeft(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps){
      moveDown(1);
      moveLeft(1);
  }  
}

void moveDiagonalUpLeft(int nNumOfSteps){
  for(int i = 0; i < nNumOfSteps){
      moveUp(1);
      moveLeft(1);
  }  
}
