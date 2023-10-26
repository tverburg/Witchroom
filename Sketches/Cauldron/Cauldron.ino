#include <SPI.h>
#include <MFRC522.h>
#include <ContinuousServo.h>


// GLOBALS
const byte numReaders = 2;
// reader data pins
const byte ssPins[] = {5, 6, 7, 8, 10};
// Array of MFRC522 instances. one for each reader
MFRC522 mfrc522[numReaders];
// NFC tag ID's required for the puzzle. respectively: {skull, card}
const String correctIDs[] = {"1798219327", "19561189148"};
// the tag IDS currently detected by each reader
String currentIDs[numReaders];

enum PuzzleState {
  UNSOLVED,
  PENDING,
  SOLVED,
  FINISHED,
  RESETTING,
};

ContinuousServo servo(2); // servo inits on pin 4
uint8_t stepsToOpen = 500;  // about 10 seconds (500 * 20ms)
uint8_t stepsToClose = -500;  // about 10 seconds (500 * 20ms)
uint8_t stepsize = 20;
uint8_t lowerStopPin = 4;
uint8_t upperStopPin = 3;

PuzzleState puzzleState = UNSOLVED;

uint8_t solvePin = 5; // admin pin for manually solving the puzzle

