#include <Stepper.h>

#define SQUARE_STEPS 10 // TEMP - CHANGE LATER
#define STEPS_PER_REVOLUTION 2048 // Steps per revolution.

 Stepper step1 = Stepper(STEPS_PER_REVOLUTION, 32, 25, 33, 26); // Creating an object of our stepper motor. // new: 26 25 33 32 old: 32, 25, 33, 26
 Stepper step2 = Stepper(STEPS_PER_REVOLUTION, 27, 13, 14, 12); // Creating an object of our stepper motor. // new: 13 12 14 27 old: 27, 13, 14, 12

void setup() {
  int notConnectedCounter = 0;
  Serial.begin(115200); // set the communication frequency to 115200Hz
  step1.setSpeed(10);
  step2.setSpeed(10); 
  delay(1000);
}

void loop() {
  //step2.step(300);
  step2.step(300);
  delay(2000);
  //step2.step(-300);
  step2.step(-300);
  delay(2000);
}
// black white red orange
// white black orange red
// black white orange red
// orange black white red
// orange red white black
// red orange white black
// white red orange black really good
// 
