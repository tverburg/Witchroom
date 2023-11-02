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
  if(!solved) {
    //ignore all inputs if the end animation is in progress
    if(!inProgress) {
      int lidButtonState = digitalRead(lidButtonPin);

      //check with the rfid readers if the puzzle is solved
      bool pieceASolved = digitalRead(alchemistReaderPinA) == HIGH;
      bool pieceBSolved = digitalRead(alchemistReaderPinB) == HIGH;

      if(pieceASolved && pieceBSolved) {
        lockLid();
      }

      if(lidButtonState == LOW) {
        Serial.println("checking");
        // Serial.println("lid button pushed, lid is closed, start checking for correct content");
      Serial.print("pieces solved : ");
      Serial.println(pieceASolved && pieceBSolved);
        if(pieceASolved && pieceBSolved) {
          Serial.println("start progress");
          // make sure the lid is locked and start the motors
          lockLid();
          inProgress = true;
        }
      }

    } else {
      onSolve();
    }
  }


  //Set the spinning direction clockwise:
  // digitalWrite(dirPin, HIGH);  ??? commented out

  // Spin the stepper motor 1 revolution slowly:
  // for (int i = 0; i < stepsPerRevolution; i++) {
  //   // These four lines result in 1 step:
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(2000);
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(2000);
  // }

  // delay(1000);

  // // Set the spinning direction counterclockwise:
  // digitalWrite(dirPin, LOW);

  // // Spin the stepper motor 1 revolution quickly:
  // for (int i = 0; i < stepsPerRevolution; i++) {
  //   // These four lines result in 1 step:
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(1000);
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(1000);
  // }

  // delay(1000);

  // // Set the spinning direction clockwise:
  // digitalWrite(dirPin, HIGH);

  // // Spin the stepper motor 5 revolutions fast:
  // for (int i = 0; i < 5 * stepsPerRevolution; i++) {
  //   // These four lines result in 1 step:
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(500);
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(500);
  // }

  // delay(1000);

  // // Set the spinning direction counterclockwise:
  // digitalWrite(dirPin, LOW);

  // //Spin the stepper motor 5 revolutions fast:
  // for (int i = 0; i < 5 * stepsPerRevolution; i++) {
  //   // These four lines result in 1 step:
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(500);
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(500);
  // }

  // delay(1000);
}