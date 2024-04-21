// ---------------------------------------------------------
// Helpers include
//
// Used for help functions that can be used thruout entire controller
//
// Predefined functions below remove if not needed
//
// Add functions below
// -------------------------------------------------------

//can be used to convert int array to string. Only useble with fixed data size. example: [5,2,6,6,2,3] --> "526623"
String convertIntArrayToString(int ints[], int size) {
  //handle resetting effects
  String string = "";

  for (int i=0; i<size; i++)
  {
    string += String(ints[i]);
  } 

  return string;
}

//last resort function that resets the arduino itself
void(* resetFunc) (void) = 0; //declare reset function @ address 0

int readMuxRunes(int channel){
  int controlPin[] = {r0, r1, r2, r3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = digitalRead(sigMuxRunePin);

  //return the value
  return val;
}

boolean checkIfRunesAreDormant(){
  boolean dormant = false;
  int count = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    if(readMuxRunes(i) == 1){
      count++;
    }
  }
  if(count == 0){
    dormant = true;
  }
  return dormant;
}

void toggleLight(int light, int state){
  digitalWrite(light, state);
}

void resetLights(){
  for (int i = 0; i < numberOfLights; i++) {
    toggleLight(i+2, LOW);
  }
}
