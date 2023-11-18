void puzzleSetup() {
  pinMode(piece1InputPin, INPUT);
  pinMode(piece2InputPin, INPUT);
  pinMode(piece3InputPin, INPUT);
  pinMode(piece4InputPin, INPUT); 

  pinMode (lockButtonInputPin, INPUT_PULLUP);
  //digitalWrite(lockButtonInputPin, HIGH); 

  pinMode(lockBoxLockPin, OUTPUT);
  digitalWrite(lockBoxLockPin, HIGH); 
  pinMode(doorLockPin, OUTPUT);
  digitalWrite(doorLockPin, LOW); 

  pinMode(cagelockPin, OUTPUT);

  pinMode(cagelockInputPin, INPUT_PULLUP);
}

void checkCageOpened() {
  int cageState = digitalRead(cagelockInputPin); // 1 is closed, 0 is open
  if(cageState == 0) {
     Serial.println(F("Open the cage"));
    // release maglock
    digitalWrite(cagelockPin, HIGH); 
  }
}

void checkDoorOpened() {
  int doorState = digitalRead(lockButtonInputPin); // 1 is closed, 0 is open
  if(doorState == 0) {
     Serial.println(F("Open the door"));
    // release maglock
    digitalWrite(doorLockPin, HIGH); 
  }
}

// Returns true if the puzzle is solved, false otherwise
bool checkIfPuzzleSolved() {
  Serial.println(F("checkIfPuzzleSolved"));

  bool changed = false;
  int piece1ValueLast = piece1Value;
  int piece2ValueLast = piece2Value;
  int piece3ValueLast = piece3Value;
  int piece4ValueLast = piece4Value;

  //todo: main state checking/setting

  //todo: piece1 state checking/setting
  piece1Value = digitalRead(piece1InputPin);
  piece2Value = digitalRead(piece2InputPin);
  piece3Value = digitalRead(piece3InputPin);
  piece4Value = digitalRead(piece4InputPin);
  changed = (piece1ValueLast != piece1Value) || (piece2ValueLast != piece2Value) || (piece3ValueLast != piece3Value) || (piece4ValueLast != piece4Value);

  Serial.println(changed);
  if(changed) {
    Serial.println(F("it changed"));
    bool solved = !piece1Value && !piece2Value && !piece3Value && !piece4Value;

    sprintf(statusUpdateMessage,"(%d,%d,%d,%d:%d)",piece1Value,piece2Value,piece3Value,piece4Value,solved);
    client.publish(publishingTopic, statusUpdateMessage);

    return solved;
  } else {
    return false;
  }
}
