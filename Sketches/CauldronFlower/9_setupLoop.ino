void setup() {
  Serial.begin(9600);
  Serial.println(F("start Serial communication"));

  SPI.begin();

  //init inputs
  pinMode(manualOpenPin, INPUT_PULLUP);
  pinMode(manualClosePin, INPUT_PULLUP);
  pinMode(lowerStopPin, INPUT_PULLUP);
  pinMode(upperStopPin, INPUT_PULLUP);

  resetPuzzle();

  Serial.println(F("----- END SETUP -----"));
}

void loop() {
  uint8_t solveInputState = digitalRead(solvePin);  //are we getting a solved signal from the CauldronTable
  uint8_t openButtonState = digitalRead(manualOpenPin);  //are we getting a manual request to open the flower
  uint8_t closeButtonState = digitalRead(manualClosePin);  //are we getting a manual request to close

  // If the puzzle is solved but the flower not yet opened,open it
  if (puzzleState == SOLVED) {
    Serial.println(F("opening"));
    //open the flower
    bool opening = openFlower();

    // if we're done opening
    if (!opening) {
      // stop
      puzzleState = FINISHED;
    }
  }

  // If the puzzle is solved but the flower not yet opened,open it
  else if (puzzleState == RESETTING) {
    Serial.println(F("closing"));
    //close the flower
    bool closing = closeFlower();

    if (!closing) {
      puzzleState = UNSOLVED;
    }
  }

  else if(puzzleState == UNSOLVED) {
    if (solveInputState == LOW) {
      puzzleState = SOLVED;
    }
  }

  // for debugging and admin purposes. To be able to externally trigger the puzzle to succeed in cases of any technical issues
  if (openButtonState == LOW) {
    puzzleState = SOLVED;
  }
  if (closeButtonState == LOW) {
    puzzleState = SOLVED;
  }
}