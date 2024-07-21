// ---------------------------------------------------------
// Locks include
//
// Used for controlling locks
//
// Use predefined functions below to control all locks on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

static boolean lockOpening = false;
static int time = 0;
const int openTime = 4000;

//called once at start
void setupLocks(){
  //add every event controlled by this controller to status array
  //Example:
  //statusObj["l"]["lock id"] = 2; //status op locks are saved here
  //statusObj["ls"]["lock id"] = 2; //states of locks are saved here
}

void resetLocks() {
  //handle resetting locks
}

//called every loop
void checkLocks(){

}
      