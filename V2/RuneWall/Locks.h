// ---------------------------------------------------------
// Locks include
//
// Used for controlling locks
//
// Use predefined functions below to control all locks on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

//called once at start
void setupLocks(){
  statusObj["l"][openDoorEvent] = 0;

  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, LOW);
}

void resetLocks() {
  //handle resetting locks
}

//called every loop
void checkLocks(){
  //handle lock stuff
  if(statusObj["l"][openDoorEvent] == 1) {
      digitalWrite(lockPin, HIGH);
  } else {
      digitalWrite(lockPin, LOW);
  }
}