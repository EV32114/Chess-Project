#include <Stepper.h>
#include <bits/stdc++.h>
#include <vector>

#define SQUARE_STEPS 10 // TEMP - CHANGE LATER
#define STEPS_PER_REVOLUTION 2048 // Steps per revolution.
#define ELECTROMAGNET_PIN 17

// #define A 3 // 21
// #define B 23 // 22
// #define C 21 // 3
// #define D 22 // 23

 //Stepper step1 = Stepper(STEPS_PER_REVOLUTION, 23, 1, 3, 22); // Creating an object of our stepper motor. // new: 26 25 33 32 old: 32, 25, 33, 26
 //Stepper step2 = Stepper(STEPS_PER_REVOLUTION, 5, 21, 18, 19); // Creating an object of our stepper motor. // new: 13 12 14 27 old: 27, 13, 14, 12
 // 23, 22, 1, 3 new: 3, 23, 1, 22 
 // 21, 19, 18, 5 new: 5, 21, 18, 19
 

void setup() {
  
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  
  
  Serial.begin(115200);
  /*std::vector<int> a;
  a.push_back(19);
  a.push_back(21);
  a.push_back(22);
  a.push_back(23);
  do{ 
    forward(a[0], a[1], a[2], a[3], 300);
    for(int i = 0; i <4; i++){
      Serial.println(a[i]);  
    }
    Serial.println();
    delay(1500);
  } while(std::next_permutation(a.begin(), a.end()));*/
  
  
  // 5 4 2 18
  // 18 2 5 4
   
  // 5 4 2 18
  // 2 18 5 4
  // 5 18 2 4
  pinMode(ELECTROMAGNET_PIN, OUTPUT); // setting up electromagnet
  digitalWrite(ELECTROMAGNET_PIN, LOW);
}

// 18 - A, 13 - D, 4 - C, 12 - B

void loop() {
  //forward(19, 23, 22, 21, 100); // WORKING
  //delay(5000);
  forward(19, 23, 22, 21, 100); // TEMP WORKING
  delay(1000);
  forward(26, 12, 14, 27, 100); // WORKING
  delay(1000);
  forward(19, 23, 22, 21, -100); // WORKING
  delay(1000);
  forward(26, 12, 14, 27, -100); // WORKING
  delay(1000);
  /* /// MOTOR CODE 
  step1.step(300);
  step2.step(300);
  delay(2000);
  step1.step(-300);
  step2.step(-300);
  delay(2000);
  // MOTOR CODE */

  /*
  digitalWrite(ELECTROMAGNET_PIN, HIGH);  // turn the Electromagnet on (HIGH is the voltage level)
  delay(5000);                            // wait for a second
  digitalWrite(ELECTROMAGNET_PIN, LOW);   // turn the Electromagnet off by making the voltage LOW
  delay(5000); 
  */
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
    delay(5);
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
      delay(5);
   } // 9 10 6 5
  }
}
