#include <SPI.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// CONSTANTS
// MAC
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
// Unique IP
const IPAddress deviceIP(192,168, 1, 31);
// Broker IP
//const IPAddress mqttServerIP(192,168,1, 93);
const IPAddress mqttServerIP(192,168, 1, 93);

// Unique name of this device, used as client ID for MQTT server and topic name
const char* deviceID = "cabinDoor";
const char* nameSpace = "witchroom/puzzles";

// Ethernet client instance
EthernetClient ethernetClient;
// MQTT client
PubSubClient MQTTclient;

// buffer to hold the messages to ben sent/have been received
char msg[64];
// The topic in which to publish a message
char topic[32];

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

unsigned long previousMillis = 0;  // will store last time input was checked
const long inputInterval = 1000;  // interval at which to check input