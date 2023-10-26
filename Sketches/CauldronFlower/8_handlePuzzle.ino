void onflowerFinished() {
  Serial.println(F("Flower movement finished"));
}

// Start opening the flower. returns true while closing. false if finished
bool openFlower() {
  bool opening = true;

  // check if we reached the end
  uint8_t endStopValue = digitalRead(lowerStopPin);
  if(endStopValue == LOW) {
    opening = false;
  }

  if(opening) {
    servo.step(stepsize, onflowerFinished);
  }

  return opening;
}

// Start closing the flower. returns true while closing. false if finished
bool closeFlower() {
  bool closing = true;

  // check if we reached the end
  uint8_t endStopValue = digitalRead(upperStopPin);
  Serial.println(endStopValue);

  if(endStopValue == LOW) {
    closing = false;
  }

  if(closing) {
    servo.step(-stepsize, onflowerFinished);
  }

  return closing;
}

void onSolve() {
  Serial.println(F("Puzzle Solved!"));
  //todo: maybe send some mqtt signal
}

void resetPuzzle() {
  Serial.println(F("Reset Puzzle"));
  puzzleState = RESETTING;
}