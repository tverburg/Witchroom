// ---------------------------------------------------------
// Locks include
//
// Used for controlling locks
//
// Use predefined functions below to control all locks on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

void openLock() {
  digitalWrite(LOCK_PIN,HIGH); // Lock to OPEN
  delay(400);
  digitalWrite(LOCK_PIN,LOW); // Lock to CLOSED, don't wait too long. It will fry the lock
  statusObj["l"][lockId] == 0; // make sure we reset the status so the lock won't fry
}

//called once at start
void setupLocks(){
  //init pin for maglock
  pinMode(LOCK_PIN, OUTPUT);

  //add every event controlled by this controller to status array
  statusObj["l"][lockId] == 0;  // for now assume the lock is closed at init. No sensor available yet
}

//handle resetting locks
void resetLocks() {
  //not needed for herbs
}

//called every loop
void checkLocks(){
  if(statusObj["l"][lockId] == 1) {
    openLock();
  }
}