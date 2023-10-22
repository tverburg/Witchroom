void setup() {
  // init input pins
  pinMode(frontDoorFinishedPin, INPUT);
  
  // init output pins
  pinMode(solveCagePin, OUTPUT);
  pinMode(solveFrontDoorPin, OUTPUT);
  pinMode(solveHerbsPuzzlePin, OUTPUT);
}

void loop() {

  manageCage();

  manageFrontDoor();

  manageHerbs();
}
