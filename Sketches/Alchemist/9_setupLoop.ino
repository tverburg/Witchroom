void setup() {
  Serial.begin(9600);
  //while (!Serial);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  pinMode(enableMotorPin, OUTPUT);

  // declare input pins
  pinMode(limitButtonPin, INPUT_PULLUP);
  pinMode(lidButtonPin, INPUT_PULLUP);
  pinMode(alchemistReaderPinA, INPUT);
  pinMode(alchemistReaderPinB, INPUT);

  //init pin values
  digitalWrite(dirPin, HIGH);
  digitalWrite(enableMotorPin, HIGH); // enabled means the motor driver is off

  resetPuzzle();

  Serial.println("Initialized");
}

void loop() {
  int lidButtonState = digitalRead(lidButtonPin);

  if(!solved) {
    //ignore all inputs if the end animation is in progress
    if(!inProgress) {
      //check with the rfid readers if the puzzle is solved
      bool pieceASolved = digitalRead(alchemistReaderPinA) == HIGH;
      bool pieceBSolved = digitalRead(alchemistReaderPinB) == HIGH;

      Serial.print("pieceASolved: ");
      Serial.print(pieceASolved);
      Serial.print(", pieceBSolved:");
      Serial.println(pieceBSolved);

      if(lidButtonState == LOW) {
       // Serial.println("lid button pushed, lid is closed, start checking for correct content");
       // Serial.print("pieces solved : ");
       // Serial.println(pieceASolved && pieceBSolved);
        
        if(pieceASolved && pieceBSolved) {
          Serial.println("start progress");
          delay(500);
          // make sure the lid is locked and start the motors
          lockLid();
          inProgress = true;
        }
      }
    } else {
      onSolve();
    }
  } else {
    //if the puzzle is solved. don lock he lid if its closed
    if(lidButtonState == LOW) {
      unlockLid();
    } else {
      lockLid();
    }
  }
}