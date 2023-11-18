void setup() {
  Serial.begin(9600);

  delay(5000); //wait a few seconds for the cauldron to finish starting

  Serial.println(F("start Serial communication"));

  //init inputs
  pinMode(manualPin, INPUT_PULLUP);
  pinMode(lowerStopPin, INPUT_PULLUP);
  pinMode(upperStopPin, INPUT_PULLUP);
  pinMode(crystalPin, INPUT_PULLUP);

  solve();

  ledSetup();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  if(!inProgress) {
    uint8_t inputState = digitalRead(manualPin); 

    if(inputState == LOW && open == false) {
      Serial.print("opening");
      solve();
    } else if (open == true) {
      uint8_t crystalPresent = digitalRead(crystalPin) == LOW; 
      if(crystalPresent) {
        Serial.println("closing wth crystal inside");
        reset();
      } else {
        Serial.println("no crystal, not closing");
      }
    }
  } else {
    if(open) {
      inProgress = openFlower();
    } else {
      inProgress = closeFlower();
    }
  }

    if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // 0 = 48, 1 = 49, enter=10
    if(incomingByte == 48) {
      reset();
    } else if(incomingByte == 49) {
      solve();
    }

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);    
  }

  ledLoop();
}