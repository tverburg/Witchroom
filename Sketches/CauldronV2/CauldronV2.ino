#include <HX711_ADC.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>

// UTP constants
byte mac[]    = { 0x2C, 0xF7, 0xF1, 0x08, 0x37, 0xA1 };
IPAddress ip(192, 168, 178, 27);
IPAddress server(192, 168, 178, 24);
// IPAddress ip(192, 168, 1, 103);
// IPAddress server(192, 168, 1, 102);
EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

long lastReconnectAttempt = 0;

const char pubResetted[] = "witchroom/p/c/resetted";
const char pubPing[] = "witchroom/p/c/ping";
const char pubMsg[] = "witchroom/p/c/msg";
const char pubSolved[] = "witchroom/p/c/solved";

const char subPing[] = "witchroom/all/pingRequest";
const char subSolve[] = "witchroom/p/c/solve";
const char subreset[] = "witchroom/p/c/reset";
const char subAll[] = "witchroom/all";

const char deviceId[] ="cauldron";
const char user[] = "shape";
const char pwd[] = "escape";

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
const int ingredientsWeights[5] = {235, 325, 515, 630, 515};
const int weightMargin = 60;
int currentWeights[5];
bool solved = false;
bool finished = false;