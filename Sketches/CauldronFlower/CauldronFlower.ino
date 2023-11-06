#include <SPI.h>
#include <ContinuousServo.h>

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

