void setup() {
  Serial.begin(9600);
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
