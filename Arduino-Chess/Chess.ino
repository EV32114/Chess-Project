const int BUTTON_PIN = 2;

void setup() {
  Serial.begin(9600); // setting baud rate to 9600.
  pinMode(BUTTON_PIN, INPUT); // setting the button pin as an input.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
  int sensorVal = digitalRead(2);
  if(sensorVal == 1){
    // if sensor val is 1, the button was pressed, 
    // and we send the appropriate data to the serial port.  
    Serial.println("H");
  }
  
  
  /**
  if(Serial.available()){
    char inByte = Serial.read();
    if(inByte == 'H'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else{
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(1);
  **/

}
