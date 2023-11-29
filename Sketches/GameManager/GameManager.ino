// The Game Manager is an arduino that monitors certain game inputs like achieved milestones and triggers certain actions accordingly
// For instance, it triggers the lights if the front door is opened.
// It also serves as a manual triggering device to solve certain puzzles manually

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// setup correctly for the used network
byte mac[] = {  0xAA, 0xBB, 0xCC, 0xDD, 0x10, 0x23 };
//IPAddress ip(192, 168, 178, 32);
IPAddress server(192, 168, 178, 24);
EthernetClient ethClient;
const char deviceID[12] = "gameManager";
const char nameSpace[] = "witchroom/managers";
const uint8_t numberOfSubscriptions = 6;
const char subTopics[][38] = {
  "witchroom/all/pingRequest",
  "witchroom/puzzles/herbs/solve",
  "witchroom/manage/frontdoor/activate",
  "witchroom/manage/frontdoor/deactivate",
  "witchroom/manage/smoke/activate",
  "witchroom/manage/smoke/deactivate"
};
const char pubTopics[][37] = {
  "witchroom/manage/gameManager/updates",
  "witchroom/puzzles/herbs/solved"
};

// outputs
const uint8_t frontDoorPin = 4;           // handles the door to the room
const uint8_t solveHerbsPuzzlePin = 5;    // manual finishing of the herbs puzzle
const uint8_t smokePin = 6;               // manual finishing of the herbs puzzle


bool solveCage = false;
bool frontDoorOpen = false;
bool herbsSolved = false;
bool smokeActive = false;
