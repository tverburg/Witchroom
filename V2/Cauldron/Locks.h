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
  //add every event controlled by this controller to status array
  //Example:
  //statusObj["l"]["event id"] = 1; //status op locks are saved here
  //statusObj["ls"]["event id"] = "[2, 4, -8, 3, 2]"; //states of locks are saved here
  statusObj["l"][boxLock] = openedlock;
}

void resetLocks() {
  statusObj["l"][boxLock] = openenlock;
}

//called every loop
void checkLocks(){
  if(statusObj["l"][boxLock] = 0) {
    statusObj["l"][boxLock] = 2;
  }

  if(statusObj["l"][boxLock] = 3) {
    statusObj["l"][boxLock] = 4;
  }
}