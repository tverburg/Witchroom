#include <ContinuousServo.h>

ContinuousServo servo(5); // servo inits on pin 4
uint8_t stepsize = 20;

uint8_t upperStopPin = 3;
uint8_t lowerStopPin = 4;
uint8_t manualPin = 2; //  pin for controlling the flower

bool inProgress = false;
bool open = false;
