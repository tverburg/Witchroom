// ---------------------------------------------------------
// Setup include
//
// Used for setting up controller
// -------------------------------------------------------

void setupJson() {
  #if hasPuzzles
    //Add puzzle dictionaries to status json (default dont touch)
    JsonObject puzzleStatusObj = statusObj["p"].to<JsonObject>();
    JsonObject puzzleProgressObj = statusObj["pi"].to<JsonObject>();
  #endif
  #if hasEvents
    //Add event dictionaries to status json (default dont touch)
    JsonObject eventsStatusObj = statusObj["e"].to<JsonObject>(); //used for saving event statuses (current status according to program)
    JsonObject eventsStatesObj = statusObj["es"].to<JsonObject>(); //used for saving event states (current state in real world.)
  #endif
  #if hasLocks
    //Add locks dictionaries to status json (default dont touch)
    JsonObject locksStatusObj = statusObj["l"].to<JsonObject>(); //used for saving locks statuses (current status according to program)
    JsonObject locksStatesObj = statusObj["ls"].to<JsonObject>(); //used for saving lock states (current state in real world)
  #endif
}

void setupComponents() {
  #if useSerial
    setupSerial();
  #endif
  #if hasPuzzles
    setupPuzzles();
  #endif
  #if hasEvents
    setupEvents();
  #endif
  #if hasLocks
    setupLocks();
  #endif
  #if hasEffects
    setupEffects();
  #endif
  #if hasTimer
    setupTimer();
  #endif
  #if hasHints
    setupHints();
  #endif
}
