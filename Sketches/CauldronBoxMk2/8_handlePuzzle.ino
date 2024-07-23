// Start opening the box. returns true while closing. false if finished
uint8_t openBox() {
  uint8_t endStopState = digitalRead(openStopPin); 
  uint8_t opening = (endStopState == HIGH ? 2 : 3);

  Serial.println(endStopState);
  Serial.println(opening); 

  if(opening == 2){
    // Set the spinning direction counterclockwise
    digitalWrite(dirPin, HIGH);

    turnMotor();
  }

  return opening;
}

// Start closing the box. returns true while closing. false if finished
uint8_t closeBox() {
  uint8_t endStopState = digitalRead(closeStopPin); 
  uint8_t closing = (endStopState == LOW ? 5 : 6);

  Serial.println(endStopState);
  Serial.println(closing); 

  if(closing == 5){
    // Set the spinning direction counterclockwise
    digitalWrite(dirPin, LOW);

    turnMotor();
  }

  return closing;
}

void enableMotor() {
  Serial.println(F("enableMotor"));
  digitalWrite(enableMotorPin, LOW); // enable motor driver
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(resetPin, HIGH); 
}

void disableMotor() {
  Serial.println(F("disableMotor"));
  digitalWrite(enableMotorPin, HIGH); // disable motor driver
  digitalWrite(sleepPin, LOW); 
  digitalWrite(resetPin, LOW); 
}

void turnMotor() {
  // Spin the stepper motor enough revolutions to move 1/3 of the box:
  for (int i = 0; i < steps; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepperSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepperSpeed);
  }
  
}

void open() {
  Serial.println(F("Solve: open box"));
  makeRed();
  enableMotor();
  doorState = openBox();

  if(doorState == 3) {
    Serial.println(F("done, disabe motor"));
    disableMotor();
  }   
}

void close() {
  Serial.println(F("Reset: close box"));
  makeBlue();
  enableMotor();
  doorState = closeBox();

  if(doorState == 6) {
    Serial.println(F("done, keep active motor")); 
  }
}

void receiveEvent(int howMany)
{
  Serial.println(F("receiveEvent"));
  int command = Wire.read();    // receive byte as an integer
  if(command == 0) {
    doorState = 4;  // 0 = close
  } else if(command == 1) {
    doorState = 1;  // 1 = open
  }
}