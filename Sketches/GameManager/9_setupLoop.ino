void setup() {
  Serial.begin(9600);
  mqttEthernetSetup();
  
  // init output pins
  pinMode(solveHerbsPuzzlePin, OUTPUT);
  pinMode(frontDoorPin, OUTPUT);
  pinMode(smokePin, OUTPUT);
  
  digitalWrite(solveHerbsPuzzlePin, HIGH);
  digitalWrite(frontDoorPin, LOW);
  digitalWrite(smokePin, LOW);
}

void loop() {
  mqttLoop();
  client.loop();

  // manageFrontDoor(true);
  // manageHerbs(false);
  // manageSmoke(false);
}
