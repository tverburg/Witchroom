void setup() {
  // init serial communication with pc
  Serial.begin(9600);
  Serial.println(F("setup"));

  // setup the ethernet connection and MQTT service
  mqttEthernetSetup();

  // setup the ethernet and mqtt connection
  puzzleSetup();

  // for (int i = 0 ; i < numberOfSubscriptions; i++) {
  //       Serial.print("Subscription check for '");
  //       Serial.print(subTopics[i]);
  //       Serial.print(" this is with index ");
  //       Serial.println(i);
  // }
}

void loop() {
  mqttLoop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= inputInterval) {
    // save the last time you checked input
    previousMillis = currentMillis;

    switch(puzzleState) {
      case Initialising:
        Serial.println(F("Initialising"));
        //initPuzzleStates();
        puzzleState = Running;
        break;
      case Running:
        //Serial.println(F("Running"));
        if(checkIfPuzzleSolved()) {
          onSolve();
        }

        break;
      case Solved:
        //if (checkIfPuzzleSolved()) {
          //onUnSolve();
        //}
        //open the lockbox
         Serial.println(F("Opening lockbox"));
        digitalWrite(lockBoxLockPin, LOW); 
        break;
    }
  }

  // listening for the key to open te door
  checkDoorOpened();

  // listening for the buttons of the cageLock to be pushed
  checkCageOpened();
}