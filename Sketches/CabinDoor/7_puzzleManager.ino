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

  pinMode(cagelockInputPin, INPUT);
}

void openCage(int id) {
  Serial.print(F("Open the cage | "));
  Serial.println(id);
  // release maglock
  digitalWrite(cagelockPin, HIGH);
  client.publish(pubTopics[4], "opened");
}

void closeCage() {
  Serial.println(F("Reset the cage"));
  // release maglock
  digitalWrite(cagelockPin, LOW);
  client.publish(pubTopics[5], "resetted");
}

void checkCageOpened() {
  int cageState = digitalRead(cagelockInputPin); // 0 is closed, 1 is open
      // Serial.println(cageState);
  if(cageState == HIGH) {
    cageHighFrameCount++;
//Serial.println("open cage?");
    //count the number of update cycles the input registers high. when a tipping point is reached we can assume it is god input an not static
    if(cageHighFrameCount >= cageTriggerFrameCount) {
      Serial.println("opening cage!");
      //doublechecked the input. solve it
      openCage(2);
    }
  } else {
    cageHighFrameCount = 0;
  }
}


void checkDoorOpened() {
  int doorState = digitalRead(lockButtonInputPin); // 1 is closed, 0 is open
  //Serial.println(doorState);
  if(doorState == 0) {
     Serial.println(F("Open the door"));
    // release maglock
    digitalWrite(doorLockPin, HIGH); 
  } 
}

// Returns true if the puzzle is solved, false otherwise
bool checkIfPuzzleSolved() {
 Serial.print(F("checkIfPuzzleSolved: "));

  bool changed = false;
  int piece1ValueLast = piece1Value;
  int piece2ValueLast = piece2Value;
  int piece3ValueLast = piece3Value;
  int piece4ValueLast = piece4Value;


  piece1Value = digitalRead(piece1InputPin);
  piece2Value = digitalRead(piece2InputPin);
  piece3Value = digitalRead(piece3InputPin);
  piece4Value = digitalRead(piece4InputPin);
  changed = (piece1ValueLast != piece1Value) || (piece2ValueLast != piece2Value) || (piece3ValueLast != piece3Value) || (piece4ValueLast != piece4Value);

Serial.print(piece1Value);
Serial.print(F(", "));
Serial.print(piece2Value);
Serial.print(F(", "));
Serial.print(piece3Value);
Serial.print(F(", "));
Serial.println(piece4Value);
  
  if(changed) {
    Serial.println(F("it changed"));
    bool solved = !piece1Value && !piece2Value && !piece3Value && !piece4Value;

    sprintf(statusUpdateMessage,"(%d,%d,%d,%d:%d)",piece1Value,piece2Value,piece3Value,piece4Value,solved);
    client.publish(pubTopics[3], statusUpdateMessage);

    return solved;
  } else {
    return false;
  }
}

void onSolve() {
  //#ifdef DEBUG
    //Serial.println("Puzzle has just been solved");
  //#endif
  // todo: do something with output pin
  // Update the global puzzle state
  puzzleState = Solved;
  // publish message to MQTT broker
  client.publish(pubTopics[1], "solved");
}

void onReset() {
  //#ifdef DEBUG
    //Serial.println(F("Puzzle has just been reset!"));
  //#endif
  // todo: reset the output pin
  // Update the global puzzle state
  puzzleState = Running;
  // publish message to MQTT broker
  client.publish(pubTopics[2], "reset");
}