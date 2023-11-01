void onflowerFinished() {
  Serial.println(F("Flower movement finished"));
}

bool openFlower() {
  bool opening = true;

  // check if we reached the end
  uint8_t endStopValue = digitalRead(lowerStopPin);
  if(endStopValue == LOW) {
        Serial.println(F("STOP!!!!"));
    opening = false;
  }

  if(opening) {
    servo.step(stepsize, onflowerFinished);
  }

  return opening;
}

bool closeFlower() {
  bool closing = true;

  // check if we reached the end
  uint8_t endStopValue = digitalRead(upperStopPin);
  Serial.println(endStopValue);

  if(endStopValue == LOW) {
    Serial.println(F("STOP!!!!"));
    closing = false;
  }

  if(closing) {
    servo.step(-stepsize, onflowerFinished);
  }

  return closing;
}

void onSolve() {
  Serial.println(F("Puzzle Solved!"));

}

void resetPuzzle() {
  Serial.println(F("Reset Puzzle"));
  puzzleState = RESETTING;
}