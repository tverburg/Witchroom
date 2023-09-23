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

  if ((servoPos == servoStart) ) // end of sweep
  {
    // stop
    closing = false;
  }

  if(closing) {
    if((millis() - lastServoUpdate) > servoUpdateInterval) { // speed to update  
        lastServoUpdate = millis();
        if(servoPos > 127) {
          servoPos++;
        } else {
          servoPos--;
        }
        flowerServo.write(servoPos);
    }
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