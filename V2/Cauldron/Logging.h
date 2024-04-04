// ---------------------------------------------------------
// Logging include
//
// Used for logging data from components
//
// Make use of logString(string) to write data to log.
//
// Dont log to much or make long string this can cause slows!!!!
// -------------------------------------------------------

#include "Memory.h"

static int maxSize = 0; //only use 50% of ram size after initialization
static String totalLogString = "";

void setupLogging(){
  maxSize = freeMemory() * 0.5;
}

void logString(const String &string) {
  byte len = totalLogString.length();
  if (string.length() + totalLogString.length() + 1 > maxSize) {
    return;
  }
  
  if (totalLogString.length() != 0) 
  {
    totalLogString += "#";
  }

  totalLogString += string;
}



