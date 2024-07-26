#define myI2cAddress 8 //I2C address this runewall arduino uses
#include <Wire.h>
#include "HC4067.h"

HC4067 mp(13, 15, 16, 17); // the 4 signal pins. a 5th can be added, which is the 'enable' pin.

//PIN declarations
const int sigMuxRunePin = 14;  // A0
// const int r0 = 13; //D13
// const int r1 = 15; //A1
// const int r2 = 16; //A2
// const int r3 = 17; //A3

//A4 and A5 are se for i2c communication
//A6 and A7 re analog inputs only
const int lightPins[] = {2,3,4,5,6,7,8,9,10,11};
const int lockPin = 12;

//volatile char runesState[22] = "0,0,0,0,0,0,0,0,0,0:0"; 
char runesState[22] = "0,0,0,0,0,0,0,0,0,0:0"; 
//char logText[] = "init";

/*
De muur der Runen bestaat uit 10 runen die verschillende afbeeldingen voorstellen.
De volgorde van de runen startend vanaf rechtsboven en dan met de klok mee. 1.Kruis, 2.Zon, 3.Heks, 4.Maan, 5.Golven, 6.Liefde, 7.Pijl, 8.Oog, 9.Vogel, 10.Ster
De oplossing is een volgorde van 5 opeenvolgende runen die de spelers uit een verhaal moeten halen.(Maan, Zon, Kruis, Heks, Liefde)
*/
struct Rune{
  boolean isActive;
};

const int numberOfLights = 10;
const int numberOfRunes = 10;
Rune runes[numberOfRunes];
const int solutionLength = 5;
const int solution[solutionLength] = {3,1,0,2,5};
boolean resetting = false;
boolean solved = false;
int activeRunes[solutionLength];
int numberOfRunesActive = 0;
long inactiveSeconds = 10000;
long currentTime;

void setup() {
  delay(1000);
  Wire.begin(myI2cAddress);     // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  delay(1000);

  //if(Serial) {
    Serial.begin(9600);
    Serial.println("init setup");

    delay(1000);
  //}

  pinMode(sigMuxRunePin, INPUT);
  delay(1000);
  
  // pinMode(r0, OUTPUT); 
  // pinMode(r1, OUTPUT); 
  // pinMode(r2, OUTPUT); 
  // pinMode(r3, OUTPUT);
  for (int i = 0; i < numberOfLights; i++) {
    pinMode(lightPins[i], OUTPUT);
  }
  pinMode(lockPin, OUTPUT);

   for(int i = 0; i < numberOfRunes; i++){

        int value = readMuxRunesV2(i);
        Serial.print(value);
        Serial.print(",");
        }
        Serial.println("----");

  for(int i = 0; i < numberOfRunes; i++){
    runes[i].isActive = false;
  }
  resetLights();
  currentTime = millis();

  resetting = false;
  solved = false;
  Serial.println("setup done");

  // char msg3[] = "setup complete";
  // strcpy(logText, msg3);
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
  //printRuneState();
  // if(millis() > currentTime + inactiveSeconds){
  //  currentTime = millis();
  //  resetLights();
  // }

  if (resetting) {
    if (checkIfRunesAreDormant()) {
      resetting = false;
      reset();
      Serial.println("resetting complete, all runes dormant");
    }
  }else{
  //check if puzzle is solved
    if(!solved){

      //check if a rune has been activated;
      
      for(int i = 0; i < numberOfRunes; i++){

        int value = readMuxRunesV2(i);

        //Serial.print("the current value of channel ");
        //Serial.print(i);
        //Serial.print(" is ");
        //Serial.print(value);

        if(value == 1){
          //if the rune had not been activated yet, set it to active and add to the activeRunes
          if(runes[i].isActive == false){
            runes[i].isActive = true;
            activeRunes[numberOfRunesActive] = i;
            numberOfRunesActive++;
            setLight(i+2, HIGH);

            uint8_t runeIndex = i*2; // the locaion of the rune in the statestring is twice the index because of the seperating comma

            noInterrupts();
            runesState[runeIndex] = '1';
             interrupts();

            Serial.print("rune: ");
            Serial.print(i);
            Serial.print(" is now active.");
            Serial.print("total of ");
            Serial.print(numberOfRunesActive);
            Serial.print(" active.");
            Serial.println();
          }
        }
      }
      //if 5 runes have been activated check if it is the correct rune order
      if(numberOfRunesActive == solutionLength){
        Serial.println("5 active runes, checking solution");
        checkIfSolved();
      } else if(numberOfRunesActive > solutionLength) {
         Serial.println("too many selected. resetting");
         resetting = true;
      }
     
    }
  }
}

void setLight(int light, int state){
  Serial.print("setLight() ");
  Serial.print(light);
  Serial.print(" to: ");
  Serial.println(state);

  digitalWrite(light, state);
}

void resetLights(){
  for (int i = 0; i < numberOfLights; i++) {
    setLight(i+2, LOW);
  }
}

void checkIfSolved(){
  int correctRunes = 0;
  for(int i = 0; i < solutionLength; i++){
    if(solution[i] == activeRunes[i]){
      correctRunes++;
    }
  }
  if(correctRunes == solutionLength){
    solve();
    Serial.println("solved bitches");
  }
  else{
    resetting = true;
  }
}

void reset(){
  resetLights();
  numberOfRunesActive = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    runes[i].isActive = false;

    uint8_t runeIndex = i*2; // the locaion of the rune in the statestring is twice the index because of the seperating comma
    runesState[runeIndex] = '0';
  }
}

boolean checkIfRunesAreDormant(){
  boolean dormant = false;
  int count = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    if(readMuxRunesV2(i) == 1){
      count++;
    }
  }
  if(count == 0){
    dormant = true;
  }
  return dormant;
}

void solve(){
  solved = true;
  digitalWrite(lockPin, HIGH);

  runesState[20] = '1';
}

void printRuneState()
{
  Serial.print("cross: ");
  Serial.print(readMuxRunesV2(0));
  Serial.print(". sun: ");
  Serial.print(readMuxRunesV2(1));
  Serial.print(", Y: ");
  Serial.print(readMuxRunesV2(2));
  Serial.print(", moon: ");
  Serial.print(readMuxRunesV2(3));
  Serial.print(", wave: ");
  Serial.print(readMuxRunesV2(4));
  Serial.print(", love: ");
  Serial.print(readMuxRunesV2(5));
  Serial.print(", arrow: ");
  Serial.print(readMuxRunesV2(6));
  Serial.print(", eye: ");                  
  Serial.print(readMuxRunesV2(7));
  Serial.print(", bird: ");
  Serial.print(readMuxRunesV2(8));
  Serial.print(", star: ");
  Serial.print(readMuxRunesV2(9));
  Serial.println();
}

int readMuxRunesV2(int channel) {
  mp.setChannel(channel);
  int val = digitalRead(sigMuxRunePin);
   //return the value
  return val;
}

// int readMuxRunes(int channel){
//   int controlPin[] = {r0, r1, r2, r3};

//   int muxChannel[16][4]={
//     {0,0,0,0}, //channel 0
//     {1,0,0,0}, //channel 1
//     {0,1,0,0}, //channel 2
//     {1,1,0,0}, //channel 3
//     {0,0,1,0}, //channel 4
//     {1,0,1,0}, //channel 5
//     {0,1,1,0}, //channel 6
//     {1,1,1,0}, //channel 7
//     {0,0,0,1}, //channel 8
//     {1,0,0,1}, //channel 9
//     {0,1,0,1}, //channel 10
//     {1,1,0,1}, //channel 11
//     {0,0,1,1}, //channel 12
//     {1,0,1,1}, //channel 13
//     {0,1,1,1}, //channel 14
//     {1,1,1,1}  //channel 15
//   };

//   //loop through the 4 sig
//   for(int i = 0; i < 4; i ++){
//     digitalWrite(controlPin[i], muxChannel[channel][i]);
//   }

//   //read the value at the SIG pin
//   int val = digitalRead(sigMuxRunePin);

//   //return the value
//   return val;
// }

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  //Serial.println(runesState);
  //char msg[] = "";
  //strcpy(msg, (const char*)runesState);
  //Wire.write(msg);
  // Wire.write(logText);

  Wire.write(runesState);
}

void receiveEvent(int howMany)
{
  int actionId = Wire.read();    // receive byte as an integer
  Serial.println(actionId);         // print the integer
  if(actionId == 0) {
    Serial.println("go reset");  
    solved = false;
    reset();
    resetFunc();
  } else if(actionId == 1) {
    Serial.println("go solve");   
    solve();
  }
}
