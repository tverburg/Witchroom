#include "Arduino.h"
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
  //init pin for maglock
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN,LOW); // Lock to CLOSED

  //add every event controlled by this controller to status array
  statusObj["l"][lockId] = closedlock;  // for now assume the lock is closed at init. No sensor available yet
}

//handle resetting locks
void resetLocks() {
    statusObj["l"][lockId] = closedlock;
}

//called every loop
void checkLocks(){
    if(statusObj["l"][lockId] == openlock) {
        time = millis();
        digitalWrite(LOCK_PIN,HIGH); // Lock to OPEN
    }
    else if( (time+lockOpenTime) < millis()) {
        digitalWrite(LOCK_PIN,LOW); // Lock to CLOSED, don't wait too long. It will fry the lock
        // make sure we reset the status so the lock won't fry
        statusObj["l"][lockId] == openedlock;
    }
}