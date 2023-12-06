#include <HX711_ADC.h>
#include <FastLED.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// UTP constants
byte mac[]    = { 0xAA, 0xBB, 0xCC, 0xDD, 0x10, 0x13 };
IPAddress ip(192, 168, 178, 27);
IPAddress server(192, 168, 178, 24);
EthernetClient ethClient;
// Unique name of this device, used as client ID for MQTT server and topic name
const char deviceID[10] = "cauldron";
const char nameSpace[] = "witchroom/puzzles";
char statusUpdateMessage[64];

//pins
const uint8_t HX711_d_1 = 14; //A0
const uint8_t HX711_sck_1 = 2;
const uint8_t HX711_d_2 = 15; //A1
const uint8_t HX711_sck_2 = 3;
const uint8_t HX711_d_3 = 16; //A2
const uint8_t HX711_sck_3 = 4;
const uint8_t HX711_d_4 = 17; //A3
const uint8_t HX711_sck_4 = 5;
const uint8_t HX711_d_5 = 18; //A4
const uint8_t HX711_sck_5 = 6;
const uint8_t flowerPin =  7;

//calibration values
const float calibrationValue_1 = 1000.00;
const float calibrationValue_2 = 1000.00;
const float calibrationValue_3 = 1000.00;
const float calibrationValue_4 = 1000.00;
const float calibrationValue_5 = 1000.00;

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
const int ingredientsWeights[5] = {235, 325, 500, 340, 620};
const int weightMargin = 30;
int currentWeights[5];
bool solved = false;
bool finished = false;

//led color palette
CRGBPalette16 gPal;