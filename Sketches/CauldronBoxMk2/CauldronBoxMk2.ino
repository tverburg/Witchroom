#include <FastLED.h>
#include <Servo.h>

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


//led color palette
CRGBPalette16 gPal;


//new
Servo myservo;  // create servo object to control a servo 
int pos = 0;

uint8_t servoPin = 4;
uint8_t openStopPin = 12;  // pin for the button which is pressed if the box is fully opened
uint8_t closeStopPin = 13;  // pin for the button which is pressed if the box is fully closed

const uint8_t LED_PIN = 11;

bool open = false;
bool inProgress = false;

unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousServoMillis = 0; // the time when the servo was last moved
const int servoMinDegrees = 0; // the limits to servo movement
const int servoMaxDegrees = 720;
int servoPosition = 90;     // the current angle of the servo - starting at 90.
int servoSlowInterval = 80; // millisecs between servo moves
int servoFastInterval = 10;
int servoInterval = servoSlowInterval; // initial millisecs between servo moves
int servoDegrees = 2;       // amount servo moves at each step 