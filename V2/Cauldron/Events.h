// ---------------------------------------------------------
// Events include
//
// Used for controlling events
//
// Use predefined functions below to control all events on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

//called once at start
void setupEvents(){
  //add every event controlled by this controller to status array
  //Example:
  //statusObj["e"]["event id"] = 1; //status op events are saved here
  //statusObj["es"]["event id"] = "[2, 4, -8, 3, 2]"; //states of events are saved here
}

void resetEvents() {
  //handle resetting events
}

void resetEventById(String eventId) {
  //handle resetting specific event based on id
}

//called every loop
void checkEvents(){
  //handle event stuff
}