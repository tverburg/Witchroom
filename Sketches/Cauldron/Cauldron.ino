#include <HX711_ADC.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>

// UTP constants
byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x37, 0xA1 };
// IPAddress ip(192, 168, 178, 27);
// IPAddress server(192, 168, 178, 24);
IPAddress ip(192, 168, 1, 103);
IPAddress server(192, 168, 1, 102);
EthernetClient ethClient;
// Unique name of this device, used as client ID for MQTT server and topic name
char statusUpdateMessage[64];

// const char pubTopics[][36] = {
//   "witchroom/puzzles/cauldron/ping",
//   "witchroom/puzzles/cauldron/msg",
//   "witchroom/puzzles/cauldron/solved",
//   "witchroom/puzzles/cauldron/resetted"
// };

//pins
const uint8_t HX711_d_1 = 14; //A0
const uint8_t HX711_sck_1 = 5;
const uint8_t HX711_d_2 = 15; //A1
const uint8_t HX711_sck_2 = 6;
const uint8_t HX711_d_3 = 16; //A2
const uint8_t HX711_sck_3 = 7;
const uint8_t HX711_d_4 = 17; //A3
const uint8_t HX711_sck_4 = 8;
const uint8_t HX711_d_5 = 2; 
const uint8_t HX711_sck_5 = 9;
const uint8_t flowerPin =  3;

//initiate loadcells
HX711_ADC LoadCell_1(HX711_d_1, HX711_sck_1);
HX711_ADC LoadCell_2(HX711_d_2, HX711_sck_2);
HX711_ADC LoadCell_3(HX711_d_3, HX711_sck_3);
HX711_ADC LoadCell_4(HX711_d_4, HX711_sck_4);
HX711_ADC LoadCell_5(HX711_d_5, HX711_sck_5);

unsigned long t = 0;
//mushrooms == loadcell 1
//feather == loadcell 2
//dragon egg == loadcel 3
//rock == loadcell 4
//apple potion == loadcell 5
const uint16_t ingredientsWeights[5] = {235, 325, 515, 630, 515};
const uint8_t weightMargin = 60;
uint8_t currentWeights[5];
bool solved = false;
bool finished = false;