#include "Arduino.h"
//controller config
#define controllerId 1
#define controlerName "herbs"

//serial config
#define baudRate 115200
#define endMarker  '\n'

//component config
#define herbsPuzzleId "1"
#define lockId "1"

/** Author: Tom van den Bulk/Thijs Verburg
  Sketch voor de kruidenkist schuifpuzzel. Elk puzzelstuk heeft 2 contactpunten oftewel 2 reed switches.
  De schuifpuzzel is een 3 bij 4 bord, met 1 leeg vak, dus 11 vakken met 2 switches een totaal van 22 reed switches.
  ================
  =  0  1  2  3  =
  =  4  X  X  5  =
  =  6  7  8  9  =
  ================
*/

//signal pin to read the state of the reed switches, the mux signal pin.
const int SIG_PIN = 2;
//Signal pin to the electric lock.
const int LOCK_PIN = 6;

//Mux control pins
const int s0 = 8;
const int s1 = 9;
const int s2 = 10;
const int s3 = 11;

// bool solved = false;
const int numberOfPins = 10;
long time;
long lockOpenTime = 400;
boolean lockOpened = false;
boolean lockActive = false;

int herbsStatusses[] = {0,0,0,0,0,0,0,0,0,0};