#include <SPI.h>

const int lidButtonPin = 4;
const int limitButtonPin = 5;
//output pins
const int enableMotorPin = 6;
const int lockPin = 7;
const int dirPin = 2;
const int stepPin = 3;
// Define stepper motor connections and steps per revolution (200 is full rotation on singlestep setup)
const int stepsPerRevolution = 200;
const int neededSteps = 116;
const int stepperSpeed = 500;
bool locked = false;

bool inProgress = false;
bool solved = false;

const uint8_t alchemistReaderPinA = 8;
const uint8_t alchemistReaderPinB = 9;
const uint8_t alchemistReaderPinC = A0;