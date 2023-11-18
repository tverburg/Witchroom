
void manageFrontDoor(bool open) {
  if(open && !frontDoorOpen) {
    digitalWrite(frontDoorPin, LOW);
    frontDoorOpen = true;
  } 
  else if(!open && frontDoorOpen) {
    digitalWrite(frontDoorPin, HIGH);
    frontDoorOpen = false;
  }
}

void manageHerbs(bool solve) {
  if(solveHerbs) {
    //send a signal to open the cage
    digitalWrite(solveHerbsPuzzlePin, HIGH);
    solveHerbs = false;
  }
}

void manageSmoke(bool activate) {

}