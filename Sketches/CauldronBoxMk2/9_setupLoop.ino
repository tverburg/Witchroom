void setup() {
  Wire.begin(7);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  delay(1000); // sanity wait

  Serial.println(F("start Serial communication"));

  // init inputs
  pinMode(crystalPin, INPUT_PULLUP);
  pinMode(openStopPin, INPUT_PULLUP);
  pinMode(closeStopPin, INPUT_PULLUP);

  pinMode(resetPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);

  // enable motor so the box cant be openend manually
  enableMotor();

  // open box on start
  open();

  ledSetup();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  //open
  if(doorState == 1) {
    Serial.println("state is open, set to opening");
    doorState = 2;
  }
  //opening
  if(doorState == 2) {
    Serial.println("state is opening ");
    open();
  }

  //close
  if(doorState == 4) {
    Serial.println("state is close, set to closing");
    doorState = 5;
  }
  //closing
  if(doorState == 5) {
    Serial.println("state is closing");
    close();
  }

  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);   

    // 0 = 48 (reset/close), 
    // 1 = 49 (solve/open), 
    // 2 = 50 stop motor
    // enter=10
    if(incomingByte == 48) { 
      doorState = 4;  // 0 = close
    } else if(incomingByte == 49) {
      doorState = 1;  // 1 = open
    } else if(incomingByte == 50) {//2
      doorState = 3;  // 2 = stop opening
    } else if(incomingByte == 51) {//3
      doorState = 6;  // 3 = stop closing
    }
  }

  ledLoop();
}