#include <FastLED.h>
#include <Wire.h>

const uint8_t stepCount = 170;
uint16_t currentSteps = 0;
const int stepperSpeed = 5000; //higher is slower

uint8_t enableMotorPin = 5;
uint8_t dirPin = 7;
uint8_t stepPin = 6;
uint8_t resetPin = 3;
uint8_t sleepPin = 4; 

uint8_t crystalPin = 9;  // pin for the button which is pressed if the crystal is present
const uint8_t LED_PIN = 13;

uint8_t steps = 40;
uint8_t openStopPin = 12;  // button pressed if the box is fully opened
uint8_t closeStopPin = 11;  // button pressed if the box is fully closed

uint8_t doOpen = 1;
uint8_t isOpening = 2;
uint8_t isOpened = 3;
uint8_t doClose = 4;
uint8_t isClosing = 5;
uint8_t isClosed = 6;

uint8_t doorState = 6;
