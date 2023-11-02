// reset the puzzle to its startpoint
void resetPuzzle() {
  Serial.println("resetPuzzle");
  
  unlockLid();

  // Set the spinning direction counterclockwise
  digitalWrite(dirPin, LOW);

  // Keep spinning the motor untill the limitbutton is reached
  bool resetting = true;
  digitalWrite(enableMotorPin, LOW); // enable motor driver

  while(resetting){
    int limitButtonState = digitalRead(limitButtonPin);

    if(limitButtonState == LOW) {
      Serial.println("limit button pushed, stop progress");
      resetting = false;
      digitalWrite(enableMotorPin, HIGH); // disable motor driver
    }

    for (int i = 0; i < stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepperSpeed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepperSpeed);
    }
  }

  inProgress = false;
  Serial.println("done resetPuzzle");
}

// If the user placed the correct items in the box, closes the lid and presses the two input buttons simultaneously. start moving the contents
void onSolve() {
  Serial.println("onSolve");

  // Set the spinning direction clockwise
  digitalWrite(dirPin, HIGH);
  digitalWrite(enableMotorPin, LOW); // enable motor driver

  // Spin the stepper motor enough revolutions to move 1/3 of the box:
  for (int i = 0; i < neededSteps * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepperSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepperSpeed);
  }

  inProgress = false;
  digitalWrite(enableMotorPin, HIGH); // disable motor driver

  unlockLid();

  Serial.println("done onSolve. stop in progress");
  solved = true;
}

void lockLid() {
  Serial.println("Lock lid");
  digitalWrite(lockPin, HIGH);
} 

void unlockLid() {
  Serial.println("Unlock lid");
  digitalWrite(lockPin, LOW);
} 