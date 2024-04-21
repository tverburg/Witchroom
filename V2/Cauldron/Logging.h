// ---------------------------------------------------------
// Logging include
//
// Used for logging data from components
//
// Make use of logString(string) to write data to log.
//
// Dont log to much or make long string this can cause slows!!!!
// -------------------------------------------------------

#include <avr/io.h>

const int maxSize = (RAMEND-RAMSTART) * 0.1; // use only 10% of total memory
static char totalLogString[maxSize] = {'|'};
static int stringSize = 0;

void clearLog() {
  for(int i = 0; i < maxSize; i++) {
    totalLogString[i]='|';
  }
  stringSize = 0;
}

void logString(const String &string) {
  byte len = string.length();

  if (stringSize + len > maxSize) 
  {
    return;
  }
  
  if (stringSize != 0) 
  {
    totalLogString[stringSize] = '#';
    stringSize += 1;
  }

  for(int i =0; i < len; i++ ) {
    totalLogString[stringSize + i] = string[i];
  }

  stringSize += len;
}

void printLogToSerial() {
  for(int i = 0; i < stringSize; i++) {
    Serial.print(totalLogString[i]);
  }
  Serial.print('\n');

  clearLog();
}


