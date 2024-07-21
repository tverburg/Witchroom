#include <ContinuousServo.h>
#include <FastLED.h>

ContinuousServo servo(4); // servo inits on pin 4
uint8_t stepsize = 20;

uint8_t upperStopPin = 3;
uint8_t lowerStopPin = 4;
uint8_t manualPin = 2;    //  pin for controlling the flower
uint8_t crystalPin = 10;  // pin for the button which is pressed if the crystal is present

bool inProgress = false;
bool open = false;

//led color palette
CRGBPalette16 gPal;