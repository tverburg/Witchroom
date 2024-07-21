void setup() {
  Serial.begin(9600);

  Serial.println(F("start"));

  //init inputs
  pinMode(openStopPin, INPUT_PULLUP);
  pinMode(closeStopPin, INPUT_PULLUP);

  // init servo control wire 
  myservo.attach(servoPin);
  // Servo is stationary.
  // myservo.write(90);

  ledSetup();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  currentMillis = millis();   // capture the latest value of millis()


   // Servo spins forward at full speed for 1 second.
  myservo.write(180);
  // delay(5000);
  // // Servo is stationary for 1 second.
  // myservo.write(180);
  // delay(5000);





  if(!open && inProgress) {
    Serial.println("opening");
    
  } else if (open && inProgress) {
    Serial.println("closing");
  }


  //done, temporary
  if(inProgress) {
    Serial.println("done");
    inProgress = false;
  }


  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);   

    // 0 = 48 (reset/close), 1 = 49 (solve/open), enter=10
    if(incomingByte == 48) {
      //reset();
    } else if(incomingByte == 49) {
      //solve();
    }
  }

  ledLoop();
}