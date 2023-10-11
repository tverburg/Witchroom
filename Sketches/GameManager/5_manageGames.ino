
void manageCage() {
  if(solveCage) {
    //send a signal to open the cage
    digitalWrite(solveCagePin, HIGH);
    solveCage = false;
  }
}

void manageFrontDoor() {
  // Assume the signal that says the door is open to be HIGH on open
  if(digitalRead(frontDoorFinishedPin) == HIGH) {
    // do stuff that should happen
  }

  if(solveFrontDoor) {
    digitalWrite(solveFrontDoorPin, HIGH);
    solveFrontDoor = false;
  }
}

void manageHerbs() {
  if(solveHerbs) {
    //send a signal to open the cage
    digitalWrite(solveHerbsPuzzlePin, HIGH);
    solveHerbs = false;
  }
}