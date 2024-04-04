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
  String string = "Ints: ";

  for (int i=0; i<size; i++)
  {
    string += String(ints[i]);
  } 

  return string;
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

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
  int val = digitalRead(SIG_PIN);

  //return the value
  return val;
}