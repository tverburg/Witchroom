void setup() {
  ethernetSetup();
  
  // init output pins
  pinMode(solveHerbsPuzzlePin, OUTPUT);
  pinMode(frontDoorPin, OUTPUT);
}

void loop() {
  ethernetLoop();

  manageFrontDoor(true);
  manageHerbs(false);
  manageSmoke(false);
}
