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
  statusObj["l"][lockId] = 0;  // for now assume the lock is closed at init. No sensor available yet
}

//handle resetting locks
void resetLocks() {
  lockOpened = false;
  lockActive = false;
}

//called every loop
void checkLocks(){
  if(statusObj["l"][lockId] == 1 && !lockOpened) {
    if(lockActive == false) {
      time = millis();
      digitalWrite(LOCK_PIN,HIGH); // Lock to OPEN
      lockActive = true;
    } 
    else if( (time+lockOpenTime) < millis()) {
      digitalWrite(LOCK_PIN,LOW); // Lock to CLOSED, don't wait too long. It will fry the lock
      lockOpened = true; // make sure we reset the status so the lock won't fry
      lockActive = false;
    }       
  }
}