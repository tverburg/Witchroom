// The Game Manager is an arduino that monitors certain game inputs like achieved milestones and triggers certain actions accordingly
// For instance, it triggers the lights if the front door is opened.
// It also serves as a manual triggering device to solve certain puzzles manually

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// setup correctly for the used network
byte mac[] = {  0xAA, 0xED, 0xBA, 0xFE, 0xFE, 0x13 };
IPAddress ip(192, 168, 178, 25);
IPAddress server(192, 168, 178, 24);

const uint8_t solveCagePin = 4;
const uint8_t solveFrontDoorPin = 5;
const uint8_t frontDoorFinishedPin = 6;
const uint8_t solveHerbsPuzzlePin = 7;

bool solveCage = false;
bool solveFrontDoor = false;
bool solveHerbs = false;
