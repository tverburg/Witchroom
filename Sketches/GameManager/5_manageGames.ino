
void manageFrontDoor(bool open) {
  Serial.print("manageFrontDoor: ");
  Serial.println(open);
  if(open && !frontDoorOpen) {
    digitalWrite(frontDoorPin, HIGH);
    frontDoorOpen = true;
  } 
  else if(!open && frontDoorOpen) {
    digitalWrite(frontDoorPin, LOW);
    frontDoorOpen = false;
  }
}

void manageHerbs(bool solve) {
  Serial.print("manageHerbs: ");
  Serial.println(solve);
  if(solve && !herbsSolved) {
    //send a signal to open the cage
    digitalWrite(solveHerbsPuzzlePin, LOW);
    herbsSolved = true;
    delay(500);
    digitalWrite(solveHerbsPuzzlePin, HIGH);
  } else {
    digitalWrite(solveHerbsPuzzlePin, HIGH);
    herbsSolved = false;
    //reset this state
  }
}

void manageSmoke(bool activate) {
  Serial.print("manageSmoke: ");
  Serial.println(activate);
  if(activate && !smokeActive) {
    digitalWrite(smokePin, HIGH);
    smokeActive = true;
    delay(20000);
    digitalWrite(smokePin, LOW);
    smokeActive = false;
  } 
  else if(!activate && smokeActive) {
    digitalWrite(smokePin, LOW);
    smokeActive = false;
  }
}