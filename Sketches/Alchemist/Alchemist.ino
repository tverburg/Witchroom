#include <SPI.h>
#include <MFRC522.h>

const int lidButtonPin = 4;
const int limitButtonPin = 5;
const int enableMotorPin = 6;
const int lockPin = 7;
const int dirPin = 2;
const int stepPin = 3;
const int rfidResetPin = 10;
// Define stepper motor connections and steps per revolution (200 is full rotation on singlestep setup)
const int stepsPerRevolution = 200;
const int neededSteps = 20;
const int stepperSpeed = 500;

bool inProgress = false;