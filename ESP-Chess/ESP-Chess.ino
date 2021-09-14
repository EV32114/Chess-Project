#include <WiFi.h>
#include <Stepper.h>


const int stepsPerRevolution = 2048;
Stepper step1 = Stepper(stepsPerRevolution, 32, 25, 33, 26);
Stepper step2 = Stepper(stepsPerRevolution, 36, 34, 39, 35);

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
      step1.step(nNumOfSteps);
      break;
      
    case 'd':
      // We move down by given number of steps
      step1.step(-nNumOfSteps);
      break;

    case 'l':
      // We move left by given number of steps
      step2.step(-nNumOfSteps);
      break;
    case 'r':
      // We move right by given number of steps
      step2.step(nNumOfSteps);
      break;
  }
}
