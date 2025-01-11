// #define RELAY_1  4  // the Arduino pin, which connects to the relay 1
// #define RELAY_2  7  // the Arduino pin, which connects to the relay 2
// #define RELAY_3  8  // the Arduino pin, which connects to the relay 3
// #define RELAY_4  12 // the Arduino pin, which connects to the relay 4

// track state of overall puzzle
enum PuzzleState {Initialising, Running, Solved, Unsolved};
PuzzleState puzzleState = Initialising;

const uint8_t cagelockPin = 12;
const uint8_t cagelockInputPin = 2;
const uint8_t lockButtonInputPin = 3;
const uint8_t piece1InputPin = A4;
const uint8_t piece2InputPin = 5;
const uint8_t piece3InputPin = 6;
const uint8_t piece4InputPin = 7;
const uint8_t lockBoxLockPin = 4; //(was 8)
const uint8_t doorLockPin = 8;   // the Arduino pin, which connects to the relay 3 (was A1)

uint8_t piece1Value;
uint8_t piece2Value;
uint8_t piece3Value;
uint8_t piece4Value;

//char statusUpdateMessage[32];

unsigned long previousMillis = 0;  // will store last time input was checked
const long inputInterval = 1000;  // interval at which to check input
uint8_t cageHighFrameCount = 0;   // amount of frames in a row the cage button is registered as high. use to check if its high for a prolonged period
uint8_t cageTriggerFrameCount = 10;   // amount of frames in a row the cage button is registered as high. use to check if its high for a prolonged period
