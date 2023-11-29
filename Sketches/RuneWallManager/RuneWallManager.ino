// Acts as the handler of messages and commands from any ethernet source to and from the runewall arduino
#define runeWallI2cAddress 8 //I2C address the runewall arduino uses

#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long checkupPeriod = 1000;  //time interval between any status update requests

const uint8_t updateMessageLength = 22;
char updateMessage[updateMessageLength] = "0,0,0,0,0,0,0,0,0,0:0";

// setup correctly for the used network
byte mac[] = {  0xAA, 0xBB, 0xCC, 0xDD, 0x10, 0x22 };
IPAddress ip(192, 168, 178, 31);
IPAddress server(192, 168, 178, 24);
EthernetClient ethClient;
const char deviceID[9] = "runeWall";
const char nameSpace[] = "witchroom/puzzles";
const uint8_t numberOfSubscriptions = 3;
const char subTopics[][33] = {
  "witchroom/all/pingRequest",
  "witchroom/puzzles/runeWall/solve",
  "witchroom/puzzles/runeWall/reset",
};
const char pubTopics[][34] = {
  "witchroom/puzzles/runeWall/msg",
  "witchroom/puzzles/runeWall/solved"
};