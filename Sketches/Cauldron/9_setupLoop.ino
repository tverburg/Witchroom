void setup() {
  Serial.begin(9600);
  Serial.println(F("start Serial communication"));

  SPI.begin();

  //init inputs
  pinMode(solvePin, INPUT_PULLUP);

  setupRFID();

  resetPuzzle();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  readRFID();

  uint8_t buttonState = digitalRead(solvePin);

  // If the puzzle is solved but the flower not yet opened,open it
  if(puzzleState == SOLVED) {
     Serial.println(F("opening"));
    //open the flower
    openFlower();
  }

  // If the puzzle is solved but the flower not yet opened,open it
  if(puzzleState == RESETTING) {
     Serial.println(F("closing"));
    //close the flower
    bool closing = closeFlower();

    if(!closing) {
      puzzleState = UNSOLVED;
    }
  }

  // for debugging and admin purposes. To be able to externally trigger the puzzle to succeed in cases of any technical issues
  if(buttonState == LOW) {
    puzzleState = SOLVED;
  }
  
}