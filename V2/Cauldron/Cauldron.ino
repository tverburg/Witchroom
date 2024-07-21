#include <ArduinoJson.h>
#include "ActionTypes.h"
#include "config.h"
#include "buildConfig.h"
#include "Helpers.h"
#include "StatusTypes.h"

#if hasPuzzles || hasEvents || hasLocks
static JsonDocument statusObj;
#endif

#if useLogging
#include "Logging.h"
#endif

#if hasPuzzles
#include "Puzzles.h"
#endif

#if hasEvents
#include "Events.h"
#endif

#if hasEffects
#include "Effects.h"
#endif

#if hasLocks
#include "Locks.h"
#endif

#if hasHints
#include "Hints.h"
#endif

#if hasTimer
#include "Timer.h"
#endif

#include "Reset.h"

#if useSerial
#include "SerialComms.h"
#endif

#include "Setup.h"

//dont touch
void setup() {
  setupJson();
  setupComponents();
  logString("Strtd"); //started
}

//dont touch
void loop() {
  //check serial communication
  #if useSerial
  checkSerial();
  #endif

  //execute check functions for components based on what arduino is used for
  #if hasPuzzles
  checkPuzzles();
  #endif
  #if hasEvents
  checkEvents();
  #endif
  #if hasEffects
  checkEffects();
  #endif
  #if hasLocks
  checkLocks();
  #endif
  #if hasHints
  checkHints();
  #endif
  #if hasTimer
  checkTimer();
  #endif
}





