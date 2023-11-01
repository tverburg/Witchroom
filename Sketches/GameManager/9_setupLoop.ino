void setup() {
  ethernetSetup();

  // init input pins
  pinMode(frontDoorFinishedPin, INPUT);
  
  // init output pins
  pinMode(solveCagePin, OUTPUT);
  pinMode(solveFrontDoorPin, OUTPUT);
  pinMode(solveHerbsPuzzlePin, OUTPUT);

}

void loop() {
  ethernetLoop();

  manageCage();

  manageFrontDoor();

  manageHerbs();
}
