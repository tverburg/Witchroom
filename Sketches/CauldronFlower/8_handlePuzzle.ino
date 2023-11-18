void onflowerFinished() {
  //Serial.println(F("Flower movement finished"));
}

// Start opening the flower. returns true while closing. false if finished
bool openFlower() {
  bool opening = true;

  // check if we reached the end
  uint8_t endStopValue = digitalRead(lowerStopPin);

  if(endStopValue == LOW) {
    Serial.println("Reached the lower pin, stop it");
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
  //Serial.println(endStopValue);

  if(endStopValue == LOW) {
    closing = false;
    Serial.println("-----");
  }

  if(closing) {
    servo.step(-stepsize, onflowerFinished);
  }

  return closing;
}

void solve() {
  Serial.println(F("Open Flower"));
  open = true;
  inProgress = true;
  makeRed();
}

void  reset() {
  Serial.println(F("Reset Flower"));
  open = false;
  inProgress = true;
  makeBlue();
}