// The Game Manager is an arduino that monitors certain game inputs like achieved milestones and triggers certain actions accordingly
// For instance, it triggers the lights if the front door is opened.
// It also serves as a manual triggering device to solve certain puzzles manually

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// setup correctly for the used network
byte mac[] = {  0xAA, 0xBB, 0xCC, 0xDD, 0x10, 0x12 };
IPAddress ip(192, 168, 178, 26);
IPAddress server(192, 168, 178, 25);

// outputs
const uint8_t frontDoorPin = 4;           // handles the door to the room
const uint8_t solveHerbsPuzzlePin = 5;    // manual finishing of the herbs puzzle

bool solveCage = false;
bool frontDoorOpen = false;
bool solveHerbs = false;
