// Start opening the box. returns true while closing. false if finished
bool openBox() {
  uint8_t endStopState = digitalRead(openStopPin); 
  bool opening = (endStopState == HIGH); 

  // if(opening){
  //   // Set the spinning direction clockwise
  //   digitalWrite(dirPin, HIGH);

  //   turnMotor(5);
  // }

  return opening;
}

// Start closing the box. returns true while closing. false if finished
bool closeBox() {
  bool opening = true;

  // // Set the spinning direction clockwise
  // digitalWrite(dirPin, LOW);

  // enableMotor();
  // turnMotor(stepCount);
  // //disableMotor();

  // opening = false;

  return opening;
}



void solve() {
  Serial.println(F("Solve: open box"));
  makeRed();
  inProgress = openBox();

  if(inProgress) {
    open = false;
  } else {
    open = true;
  }
}

void reset() {
  Serial.println(F("Reset: close box"));
  makeBlue();
  closeBox();

  open = false;
}
