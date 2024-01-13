void setup() {
  // Wire.begin(7);
  // Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  delay(5000); //wait a few seconds for the cauldron to finish starting

  Serial.println(F("start Serial communication"));

  //init inputs
  pinMode(manualPin, INPUT_PULLUP);
  pinMode(crystalPin, INPUT_PULLUP);
  pinMode(endStopPin, INPUT_PULLUP);

  pinMode(resetPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);

  enableMotor();
  //disableMotor();


  solve();

  ledSetup();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  uint8_t inputState = digitalRead(manualPin); 
  bool changed = false;
  if(previousInputState != inputState) {
    changed = true;
    previousInputState = inputState;
  }
//Serial.println(inputState);
  

  if(changed) {
    Serial.println("it changed");
    if(inputState == LOW && open == false) {
      Serial.println("opening");
      inProgress = true;
    } else if (inputState == HIGH && open == true) {
      Serial.println("closing");
      reset();
    }
  }

  if(inProgress) {
    solve();
  }

  // uint8_t crystalPresent = digitalRead(crystalPin) == LOW; 
  // if(crystalPresent) {
  //   Serial.println("closing wth crystal inside");

  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);   

    // 0 = 48 (reset/close), 1 = 49 (solve/open), enter=10
    if(incomingByte == 48) {
      reset();
    } else if(incomingByte == 49) {
      solve();
    }
  }

  ledLoop();
}