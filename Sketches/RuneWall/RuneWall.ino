// Capacitive sensing without actually touching can cause pretty erratic input causing inputs to go to "untouched" pretty quickly
// So the following strategy is implemented. If a sensor senses it is "touched", the the state goes to "On" and 
// will stop recording input for the amount of ms defined in "unresponsiveTime". After said time it will go back to listening for input. Requiring another
// "touched" input to go back to ther "Off" state. 
// Ie: it is a toggle button, only toggled by being touched and having a delay to make sur it is not toggle off again when someone moves their hand away

//runes, clockwise staring at 7:00
// 1: ster        2: vliegen    3: oog                4: man/krijger    5: romantiek 
// 6: kruispunt   7:zon         8: vrouw/priesteres   9: maan           10: golven
// hint: "Onder de bloedmaan zien krijger en priesteres elkaar, hun ogen stralend als de zon, in betovering." => 9, 4, 8, 3, 7

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

struct Rune{
  uint8_t id;
  boolean active;
  uint16_t updated;
};

enum puzzleState {
  UNSOLVED,
  PENDING_SOLVED,
  SOLVED, 
};

Adafruit_MPR121 cap = Adafruit_MPR121();  // init capacitive sensor
const uint8_t numberOfRunes = 10;
Rune runes[numberOfRunes] = {};
const uint8_t solutionLength = 5;
const uint8_t solution[solutionLength] = {9, 4, 8, 3, 7};
const uint8_t currentInput[solutionLength] = {};

const uint8_t runePins[numberOfRunes] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const uint8_t lockPin = 3;

unsigned long currentMillis;
unsigned long pausedMillis = 0;
bool paused = false;
const unsigned long unresponsiveTime = 2000;  // the amount of ms an input waits after registering a "touched" input

uint8_t activeCounter = 0; // how many runes are currently active

