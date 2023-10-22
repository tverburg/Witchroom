void onflowerFinished() {
  Serial.println(F("Flower movement finished"));
}

void openFlower() {
  if((millis() - lastServoUpdate) > servoUpdateInterval) {  // speed to update
      lastServoUpdate = millis();
      servoPos++;
      flowerServo.write(servoPos);
      if ((servoPos >= servoEnd) ) // end of sweep
      {
        // stop
        puzzleState = FINISHED;
      }
  }
}

bool closeFlower() {
  bool closing = true;

  if(closing) {
    servo.step(stepsToClose, onflowerFinished);
    closing = false;
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