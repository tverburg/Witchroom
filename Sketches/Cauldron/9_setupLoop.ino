void setup() {
  Serial.begin(9600);
  mqttEthernetSetup();

  Serial.println(F("starting setup"));

  delay(10);

  //define pins
  pinMode(flowerPin, OUTPUT);

  //init defaults
  reset();

  startupScales();
}

void loop() {  
  mqttLoop();
  // put your main code here, to run repeatedly:
  if (!solved) {
    readValues();
    checkSolution();
  } else if(!finished) {
    solve();
  }

  if(Serial.available() > 0) {
    // read inoming byte:
    int incomingByte = Serial.read();

    //0=48, 1=49, enter=10
    if(incomingByte == 48) {
      reset();
    } else if(incomingByte == 49){
      solve();
    }

    //say what you got:
    Serial.print(F("Received from serial: "));
    Serial.println(incomingByte);
  }
}