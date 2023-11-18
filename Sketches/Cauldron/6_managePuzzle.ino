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
  Serial.println(publishingTopic);
  client.publish(publishingTopic, "resetted");
}

void solve(){
  Serial.println(F("solve"));
  digitalWrite(flowerPin, LOW);
  finished = true;
  solved = true;
  Serial.println(publishingTopic);
  client.publish(publishingTopic, "solved");
}