#include <CapacitiveSensor.h>

#define RUNE_COUNT 1

CapacitiveSensor rune1_input = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
const int rune1_threshold = 100;
const bool rune1_state = false;
const int rune1_outputPin = 12;

const int outputPins[RUNE_COUNT] = {rune1_outputPin};   // the pins that trigger a rune light change
bool states[RUNE_COUNT] = {rune1_state};                // the states of the runes true = active/pressed
bool hovering[RUNE_COUNT] = {rune1_state};              // are we hovering over a rune. a combination of state and hover trigers a state change.
const int thresholds[RUNE_COUNT] = {rune1_threshold};   // the values of capacitance that need to be exceeded for a rune to be triggerd as active or hovering
CapacitiveSensor inputs[RUNE_COUNT] = {rune1_input};    // the sensor inputs

void setup()                    
{
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(rune1_outputPin, OUTPUT);
}

void loop()                    
{
  //long start = millis();
  //Serial.print(millis() - start);        // check on performance in milliseconds
  //Serial.println("\t");                  // tab character for debug windown spacing

  for(int i=0;i < RUNE_COUNT; i++) {
    long input =  inputs[i].capacitiveSensor(30);
    Serial.println(input);                  
    
    // check if we detect a hovering hand
    if(input > thresholds[i]) {
      // see if we were not already hovering. if not, toggle active and set hovering
      if(!hovering[i]) {
        states[i] = !states[i];
        hovering[i] = true;
      }
    } 
    // we detect no hovering hand
    else {
      // see if we were hovering before. if so, set hovering
      if(hovering[i]) {
        hovering[i] = false;
      }
    }

    if(states[i] == true) {
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(outputPins[i], HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(outputPins[i], LOW);
    }
  }

  delay(100);                             // arbitrary delay to limit data to serial port 
}