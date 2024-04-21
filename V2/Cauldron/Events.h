// ---------------------------------------------------------
// Events include
//
// Used for controlling events
//
// Use predefined functions below to control all events on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

void resetEvents() {
  //handle resetting events
  statusObj["e"][openBoxEvent] = 0; 
  statusObj["e"][closeBoxEvent] = 0; 
}

//called once at start
void setupEvents(){
  //add every event controlled by this controller to status array
  resetEvents();
}

void resetEventById(String eventId) {
  statusObj["e"][eventId] = 0; 
}

//called every loop
void checkEvents(){
  if(statusObj["e"][openBoxEvent] = 1) {
    sendOpenBox();
    statusObj["e"][openBoxEvent] = 2;
  }

  if(statusObj["e"][closeBoxEvent] = 1) {
    sendCloseBox();
    statusObj["e"][closeBoxEvent] = 2;
  }
}