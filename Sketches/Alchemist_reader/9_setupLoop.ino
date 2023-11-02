void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Starting up");

  // Declare pins as output:
  pinMode(outputPinA, OUTPUT);
  digitalWrite(outputPinA, LOW);
  pinMode(outputPinB, OUTPUT);
  digitalWrite(outputPinB, LOW);

  // Declare pins as output:
   pinMode(resetPin, INPUT);
  
  setupRFID();

  Serial.println("Initialized");
}

void loop() {
  uint8_t resetState = digitalRead(resetPin);

  if(resetState == HIGH && resetting == false) {
    resetting = true;
    resetReader();
  } else if(resetState == LOW && resetting == true) {
    resetting = false;
  }

    uint8_t puzzleState = isPuzzleSolved();
    Serial.println(puzzleState);

    //puzzleState returns an id for the states of the 2 readers. 1:A- & B-, 2:A+ & B-, 3:A- && B+, 4:A+ & B+
    //  |-----|-----|
    //  |  A  |     |
    //  |  B  |     |
    //  |_____|_____|

    switch(puzzleState) {
      case 2:
        digitalWrite(outputPinA, HIGH);
        digitalWrite(outputPinB, LOW);
        break;
      case 3:
        digitalWrite(outputPinA, LOW);
        digitalWrite(outputPinB, HIGH);
        break;
      case 4:
        digitalWrite(outputPinA, HIGH);
        digitalWrite(outputPinB, HIGH);
        break;
      default:
        digitalWrite(outputPinA, LOW);
        digitalWrite(outputPinB, LOW);
    }
}