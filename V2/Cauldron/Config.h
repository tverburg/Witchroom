//controller config
#define controllerId 3
#define controlerName "cauldron"

//serial config
#define baudRate 1000000
#define endMarker  '\n'

//component config
#define cauldronPuzzle 1
#define openBoxEvent 1
#define closeBoxEvent 2

char statusUpdateMessage[64];

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

const uint8_t crystalPin =  3;


//calibration values
const float calibrationValue_1 = 1000.00;
const float calibrationValue_2 = 1000.00;
const float calibrationValue_3 = 1000.00;
const float calibrationValue_4 = 1000.00;
const float calibrationValue_5 = 1000.00;

//mushrooms == loadcell 1
//feather == loadcell 2
//dragon egg == loadcel 3
//rock == loadcell 4
//potion == loadcell 5

//initiate loadcells
HX711_ADC LoadCell_1(HX711_d_1, HX711_sck_1);
HX711_ADC LoadCell_2(HX711_d_2, HX711_sck_2);
HX711_ADC LoadCell_3(HX711_d_3, HX711_sck_3);
HX711_ADC LoadCell_4(HX711_d_4, HX711_sck_4);
HX711_ADC LoadCell_5(HX711_d_5, HX711_sck_5);

const int ingredientsWeights[5] = {235, 325, 515, 630, 515};
const int weightMargin = 60;
int currentWeights[5];
bool sendingI2c = false;

