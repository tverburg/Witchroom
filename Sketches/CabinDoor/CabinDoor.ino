#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// UTP constants
byte mac[]    = { 0xAA, 0xBB, 0xCC, 0xDD, 0x10, 0x11 };
//IPAddress ip(192, 168, 178, 25);
IPAddress server(192, 168, 178, 24);
EthernetClient ethClient;
// Unique name of this device, used as client ID for MQTT server and topic name
const char deviceID[10] = "cabinDoor";
const char nameSpace[] = "witchroom/puzzles";

// track state of overall puzzle
enum PuzzleState {Initialising, Running, Solved, Unsolved};
PuzzleState puzzleState = Initialising;

const uint8_t cagelockPin = A3;
const uint8_t cagelockInputPin = A4;
const uint8_t lockButtonInputPin = 3;
const uint8_t piece1InputPin = 4;
const uint8_t piece2InputPin = 5;
const uint8_t piece3InputPin = 6;
const uint8_t piece4InputPin = 7;
const uint8_t lockBoxLockPin = 8;
const uint8_t doorLockPin = A1;

uint8_t piece1Value;
uint8_t piece2Value;
uint8_t piece3Value;
uint8_t piece4Value;

char statusUpdateMessage[32];

unsigned long previousMillis = 0;  // will store last time input was checked
const long inputInterval = 1000;  // interval at which to check input