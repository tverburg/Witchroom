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
const int piece1InputPin = 4;
int piece1Value;
const int piece2InputPin = 5;
int piece2Value;
const int piece3InputPin = 6;
int piece3Value;
const int piece4InputPin = 7;
int piece4Value;

const int lockButtonInputPin = 3;
const int lockBoxLockPin = 9;



unsigned long previousMillis = 0;  // will store last time input was checked
const long inputInterval = 1000;  // interval at which to check input

void setup() {
  // init serial communication with pc
  Serial.begin(9600);
  Serial.println(F("setup"));


  // setup the ethernet connection
  // ethernetSetup();
  // setup the MQTT service
  // mqttSetup();
  // setup the ethernet and mqtt connection
  puzzleSetup();
  
  //mqttEthernetSetup();
}

void puzzleSetup() {
  pinMode (piece1InputPin, INPUT);
  pinMode (piece2InputPin, INPUT);
  pinMode (piece3InputPin, INPUT);
  pinMode (piece4InputPin, INPUT); 

  pinMode (lockButtonInputPin, INPUT);
  digitalWrite(lockButtonInputPin, HIGH); 

  pinMode (lockBoxLockPin, OUTPUT);
}

void loop() {

  // Call the MQTT loop
  //mqttLoop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= inputInterval) {
    // save the last time you checked input
    previousMillis = currentMillis;

    switch(puzzleState) {
      case Initialising:
        Serial.println(F("Initialising"));
        initPuzzleStates();
        puzzleState = Running;
        break;
      case Running:
        Serial.println(F("Running"));
        if(checkIfPuzzleSolved()) {
          onSolve();
        }

        // todo: move to appropriate position in code
        checkDoorOpened();

        break;
      // case Solved:
      //   if (checkIfPuzzleSolved()) {
      //     onUnSolve();
      //   }
      //   break;
    }
  }
}

void checkDoorOpened() {
  int doorState = digitalRead(lockButtonInputPin); // 1 is closed, 0 is open
  if(doorState == 0) {
     Serial.println(F("Open the door"));
    // todo: release maglock
  }
}

// Returns true if the puzzle is solved, false otherwise
bool checkIfPuzzleSolved() {
  Serial.println(F("checkIfPuzzleSolved"));

  bool changed = false;
  int piece1ValueLast = piece1Value;
  int piece2ValueLast = piece2Value;
  int piece3ValueLast = piece3Value;
  int piece4ValueLast = piece4Value;

  //todo: main state checking/setting

  //todo: piece1 state checking/setting
  piece1Value = digitalRead(piece1InputPin);
  piece2Value = digitalRead(piece2InputPin);
  piece3Value = digitalRead(piece3InputPin);
  piece4Value = digitalRead(piece4InputPin);
  changed = (piece1ValueLast != piece1Value) || (piece2ValueLast != piece2Value) || (piece3ValueLast != piece3Value) || (piece4ValueLast != piece4Value);

  Serial.println(changed);
  if(changed) {
    Serial.println(F("it changed"));
    StaticJsonDocument<48> puzzleObject;
    JsonObject pieces = puzzleObject.createNestedObject("pieces");
    puzzleObject["state"] = !piece1Value && !piece2Value && !piece3Value && !piece4Value;
    puzzleObject["pieces"]["piece1"] = !piece1Value;
    puzzleObject["pieces"]["piece2"] = !piece2Value;
    puzzleObject["pieces"]["piece3"] = !piece3Value;
    puzzleObject["pieces"]["piece4"] = !piece4Value;

    // serializeJson(puzzleObject, Serial);
    // Serial.println();
    char serializedMessage[110];
    serializeJson(puzzleObject, serializedMessage); 
    publish(serializedMessage);

    return puzzleObject["state"];
  } else {
    return false;
  }
}
