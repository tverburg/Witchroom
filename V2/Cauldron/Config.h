//controller config
#define controllerId 4
#define controlerName "cauldron"

//serial config
#define baudRate 1000000
#define endMarker  '\n'

//component config
#define boxLockId 5
#define boxLightsEffectId 1

//stepper motor settings
const int stepperSpeed = 5000; //higher is slower
uint8_t steps = 40;

//pins
uint8_t enableMotorPin = 5;
uint8_t dirPin = 7;
uint8_t stepPin = 6;
uint8_t resetPin = 3;
uint8_t sleepPin = 4; 

// uint8_t crystalPin = 9;  // pin for the button which is pressed if the crystal is present. not supported yet
const uint8_t LED_PIN = 13;

uint8_t openStopPin = 12;  // button pressed if the box is fully opened
uint8_t closeStopPin = 11;  // button pressed if the box is fully closed
