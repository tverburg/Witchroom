// ---------------------------------------------------------
// Effects include
//
// Used for controlling effects
//
// Use predefined functions below to control all effects on controller
// -------------------------------------------------------

//called once at start
void setupEffects(){
  //do setup for effects here
}

void resetEffects() {
  //handle resetting effects
}

void resetEffectById(String effectId) {
  //handle resetting specific effect based on id
}

//called every loop
void checkEffects(){
  //handle effects stuff
}

//called when host pc executes special effect
//name and value for special are passed
//only save data needed for special execute in checkEffects()
void receivedSpecial(String name, String value) {
  //handle receiving special effects
}