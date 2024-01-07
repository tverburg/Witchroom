#include <FastLED.h>
#include <Wire.h>

const uint8_t stepCount = 170;
uint16_t currentSteps = 0;
const int stepperSpeed = 5000; //higher is slower

uint8_t enableMotorPin = 4;
uint8_t dirPin = 2;
uint8_t stepPin = 3;
uint8_t resetPin = 6;
uint8_t sleepPin = 5; 

// uint8_t upperStopPin = 3;
// uint8_t lowerStopPin = 4;
uint8_t manualPin = 12;    //  pin for controlling the box
uint8_t endStopPin = 10;  // pin for the button which is pressed if the crystal is present
uint8_t crystalPin = 9;  // pin for the button which is pressed if the crystal is present
const uint8_t LED_PIN = 11;

bool inProgress = false;
bool open = false;
uint8_t previousInputState = 1;

//led color palette
CRGBPalette16 gPal;