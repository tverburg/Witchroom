void setup() {
  Serial.begin(9600);
  Serial.println(F("start Serial communication"));

  //init inputs
  pinMode(manualPin, INPUT_PULLUP);
  pinMode(lowerStopPin, INPUT_PULLUP);
  pinMode(upperStopPin, INPUT_PULLUP);

  reset();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  if(!inProgress) {
    uint8_t inputState = digitalRead(manualPin); 

    if(inputState == LOW && open == false) {
      open = true;
      inProgress = true;
    } else if (inputState == HIGH && open == true) {
      open = false;
      inProgress = true;
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
}