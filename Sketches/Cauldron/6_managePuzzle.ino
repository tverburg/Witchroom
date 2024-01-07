void checkSolution(){
  int correctWeights = 0;
  for (int i = 0 ; i < 5; i++) {
    if (currentWeights[i] + weightMargin >= ingredientsWeights[i] &&
          currentWeights[i] - weightMargin <= ingredientsWeights[i]) {
          correctWeights++;
    }
  }
  if (correctWeights == 5) {
    Serial.println(F("solved bitches"));
    solved = true;
  }
}

void reset() {
  Serial.println(F("reset, publish to "));
  finished = false;
  solved = false;
  digitalWrite(flowerPin, HIGH);
  sendReset();
  Serial.println(publishingTopic);
  client.publish(publishingTopic, "resetted");
}

void solve(){
  Serial.println(F("solve"));
  digitalWrite(flowerPin, LOW);
  finished = true;
  solved = true;
  sendSolve();
  Serial.println(publishingTopic);
  client.publish(publishingTopic, "solved");
}

void sendSolve() {
  Wire.beginTransmission(7); // transmit to device #7 (crystal box)
  Wire.write(1);              // sends one byte. 1 means solve
  Wire.endTransmission();    // stop transmitting
}

void sendReset() {
  Wire.beginTransmission(7); // transmit to device #7 (crystal box)
  Wire.write(0);              // sends one byte. 0 means reset
  Wire.endTransmission();    // stop transmitting
}