#include <SPI.h>
#include <ContinuousServo.h>
#include "HX711-multi.h"

enum PuzzleState {
  UNSOLVED,
  PENDING,
  SOLVED,
  FINISHED,
  RESETTING,
};

PuzzleState puzzleState = UNSOLVED;

ContinuousServo servo(2); // servo inits on pin 4
uint8_t stepsize = 20;

uint8_t upperStopPin = 3;
uint8_t lowerStopPin = 4;
uint8_t manualClosePin = 5; //  pin for manually closing the flower
uint8_t manualOpenPin = 6; //  pin for manually opening the puzzle
uint8_t solvePin = 7;

uint8_t CLK = A0    ;  // clock pin to the load cell amp
uint8_t DOUT1 = A1 ;   // data pin to the first lca
uint8_t TARE_TIMEOUT_SECONDS = 4;
const uint8_t CHANNEL_COUNT = 1;
byte DOUTS[CHANNEL_COUNT] = {DOUT1};

long int results[CHANNEL_COUNT];
HX711MULTI scales(CHANNEL_COUNT, DOUTS, CLK);

