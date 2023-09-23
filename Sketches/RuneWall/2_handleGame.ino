void debugStuff() {
  //   for(int i=0; i < numberOfRunes; i++) {
  //     Serial.print(F("id: "));
  //     Serial.print(runes[i].id);
  //     Serial.print(F(", active: "));
  //     Serial.print(runes[i].active);
  //     Serial.print(F(", updated: "));
  //     Serial.println(runes[i].updated);
  // };
  Serial.print(F("activeCounter: "));
  Serial.print(activeCounter);
  Serial.print(F(", paused: "));
  Serial.print(paused);
  Serial.print(F(", diff: "));
  Serial.print( (currentMillis - pausedMillis));
 
  

    for(int i=0; i < numberOfRunes; i++) {
      if(runes[i].active) {
        Serial.print(runes[i].id);
      }
  };
Serial.println();
}

void resetRunes() {
  // hold input for a short while
  paused = true;
  pausedMillis = currentMillis;

  for (uint8_t i=0; i<numberOfRunes; i++) {
    runes[i].active = false;
    digitalWrite(runePins[i], LOW);
  }
  activeCounter = 0;
}

// checks the current input to see if the puzzle is solved or not
bool isPuzzleSolved() {
  // assume the puzzle is solved
  bool solved = true;

  // loop through current inputs and check them
  for(uint8_t i=0; i < solutionLength; i++) {
    // if just one of them does not match, the puzzle failed
    if(currentInput[i] != solution[i]) {
      solved = false;
    }
  }


  if(activeCounter == solutionLength) {
     Serial.print(F("5 entries found, validating"));
    // reset the puzzle if all 5 items are filled but the puzzle is not solved
    if(!solved) {
       Serial.print(F("not solved..."));
      resetRunes();
    } else {
       Serial.print(F("solved!!!"));
    }
  }

  return solved;
}