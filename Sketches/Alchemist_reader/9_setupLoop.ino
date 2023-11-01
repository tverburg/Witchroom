void setup() {
  Serial.begin(9600);
  //while (!Serial);

  // Declare pins as output:
  pinMode(outputPinA, OUTPUT);
  digitalWrite(outputPinA, LOW);
  pinMode(outputPinB, OUTPUT);
  digitalWrite(outputPinB, LOW);
  
  setupRFID();

  Serial.println("Initialized");
}

void loop() {
    uint8_t puzzleState = isPuzzleSolved();

    //puzzleState returns an id for the states of the 2 readers. 0:incorrect-incorrect, 1:correct-incorrect, 2:incorrect-correct, 3:correct-correct 

    if(puzzleState) {
      digitalWrite(outputPinA, HIGH);
    } else {
      digitalWrite(outputPinA, LOW);
    }
}