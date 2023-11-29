void setup() {
  Wire.begin(9);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  Serial.begin(9600);  // start serial for output

  startMillis = millis();  //initial start time

  Serial.println("Runewall manager setup complete");

  mqttEthernetSetup();
}

void loop() {
  mqttLoop();
  
  currentMillis = millis();  

  //test whether the update period has elapsed
  if (currentMillis - startMillis >= checkupPeriod) {
    requestRuneStatus();
    startMillis = currentMillis;  //reset the timer
  }

  // for manual commands
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // 0 = 48, 1 = 49, enter=10
    if(incomingByte == 48) {
      reset();
    } else if(incomingByte == 49) {
      solve();
    } else if(incomingByte == 50) {
      requestRuneStatus();
    }

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);    
  }
}