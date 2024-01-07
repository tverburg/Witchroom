// Start opening the box. returns true while closing. false if finished
bool openBox() {
  uint8_t endStopState = digitalRead(endStopPin); 
  bool opening = (endStopState == HIGH); 

  if(opening){
    // Set the spinning direction clockwise
    digitalWrite(dirPin, HIGH);

    turnMotor(5);
  }

  return opening;
}

// Start closing the box. returns true while closing. false if finished
bool closeBox() {
  bool opening = true;

  // Set the spinning direction clockwise
  digitalWrite(dirPin, LOW);

  enableMotor();
  turnMotor(stepCount);
  //disableMotor();

  opening = false;

  return opening;
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

void turnMotor(uint8_t steps) {
  
  // Spin the stepper motor enough revolutions to move 1/3 of the box:
  for (int i = 0; i < steps; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepperSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepperSpeed);
  }
  
}

void solve() {
  Serial.println(F("Solve: open box"));
  makeRed();
  enableMotor();
  inProgress = openBox();

  if(inProgress) {
    open = false;
  } else {
    disableMotor();
    open = true;
  }
}

void reset() {
  Serial.println(F("Reset: close box"));
  makeBlue();
  closeBox();

  open = false;
}

void receiveEvent(int howMany)
{
  int command = Wire.read();    // receive byte as an integer
  if(command == 0) {
    reset();
  } else if(command == 1) {
    solve();
  }
}