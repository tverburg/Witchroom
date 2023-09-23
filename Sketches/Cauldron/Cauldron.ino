#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


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

Servo flowerServo;
uint8_t flowerServoPin = 4;
long lastServoUpdate = 0;        // will store the time the servo started
long servoUpdateInterval = 1;           // time to wait for servo to move from start t finish
uint8_t servoStart = 0; // don't change!
uint8_t servoEnd = 90;
uint8_t servoPos = 0;
PuzzleState puzzleState = UNSOLVED;

uint8_t solvePin = 5; // admin pin for manually solving the puzzle

