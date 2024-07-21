// ---------------------------------------------------------
// Puzzles include
//
// Used for controlling puzzles
//
// Use predefined functions below to control all puzzles on controller
// -------------------------------------------------------
extern JsonDocument statusObj;

void startupScales(){
  LoadCell_1.begin();
  LoadCell_2.begin();
  LoadCell_3.begin();
  LoadCell_4.begin();
  LoadCell_5.begin();

  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  byte loadcell_1_rdy = 0;
  byte loadcell_2_rdy = 0;
  byte loadcell_3_rdy = 0;
  byte loadcell_4_rdy = 0;
  byte loadcell_5_rdy = 0;
  while ((loadcell_1_rdy + loadcell_2_rdy + loadcell_3_rdy + loadcell_4_rdy + loadcell_5_rdy) < 5) { //run startup, stabilization and tare, both modules simultaniously
    if (!loadcell_1_rdy) loadcell_1_rdy = LoadCell_1.startMultiple(stabilizingtime, _tare);
    if (!loadcell_2_rdy) loadcell_2_rdy = LoadCell_2.startMultiple(stabilizingtime, _tare);
    if (!loadcell_3_rdy) loadcell_3_rdy = LoadCell_3.startMultiple(stabilizingtime, _tare);
    if (!loadcell_4_rdy) loadcell_4_rdy = LoadCell_4.startMultiple(stabilizingtime, _tare);
    if (!loadcell_5_rdy) loadcell_5_rdy = LoadCell_5.startMultiple(stabilizingtime, _tare);
  }
  if (LoadCell_1.getTareTimeoutFlag()) {
    logString(F("HX711 1 error"));
  }
  if (LoadCell_2.getTareTimeoutFlag()) {
    logString(F("HX711 2 error"));
  }
  if (LoadCell_3.getTareTimeoutFlag()) {
    logString(F("HX711 3 error"));
  }
  if (LoadCell_4.getTareTimeoutFlag()) {
    logString(F("HX711 4 error"));
  }
  if (LoadCell_5.getTareTimeoutFlag()) {
    logString(F("HX711 5 error"));
  }
  LoadCell_1.setCalFactor(calibrationValue_1); 
  LoadCell_2.setCalFactor(calibrationValue_2); 
  LoadCell_3.setCalFactor(calibrationValue_3); 
  LoadCell_4.setCalFactor(calibrationValue_4); 
  LoadCell_5.setCalFactor(calibrationValue_5); 
}

void readValues(){
  static boolean newDataReady = 0;
  
  // check for new data/start next conversion:
  if (LoadCell_1.update())  { newDataReady = true; }
  if (LoadCell_2.update())  { newDataReady = true; }
  if (LoadCell_3.update())  { newDataReady = true; }
  if (LoadCell_4.update())  { newDataReady = true; }
  if (LoadCell_5.update())  { newDataReady = true; }

  //get smoothed value from data set
  if ((newDataReady)) {
    int a = LoadCell_1.getData();currentWeights[0] = a;
    int b = LoadCell_2.getData();currentWeights[1] = b;
    int c = LoadCell_3.getData();currentWeights[2] = c;
    int d = LoadCell_4.getData();currentWeights[3] = d;
    int e = LoadCell_5.getData();currentWeights[4] = e;

    sprintf(statusUpdateMessage,"%d,%d,%d,%d,%d",a,b,c,d,e);
    statusObj["pi"][cauldronPuzzle] = statusUpdateMessage;

    newDataReady = 0;
  }
}

//use i2c for now. todo: move box to own arduino in the network
void sendOpenBox() {
  Wire.beginTransmission(7); // transmit to device #7 (crystal box)
  Wire.write(1);              // sends one byte. 1 means solve
  Wire.endTransmission();    // stop transmitting
}

void sendCloseBox() {
  Wire.beginTransmission(7); // transmit to device #7 (crystal box)
  Wire.write(0);              // sends one byte. 0 means reset
  Wire.endTransmission();    // stop transmitting
}

void solve(){
  statusObj["p"][cauldronPuzzle] = 1;
  digitalWrite(crystalPin, LOW);
  sendOpenBox();
}

void checkSolution(){
  int correctWeights = 0;
  for (int i = 0 ; i < 5; i++) {
    if (currentWeights[i] + weightMargin >= ingredientsWeights[i] &&
          currentWeights[i] - weightMargin <= ingredientsWeights[i]) {
          correctWeights++;
    }
  }
  if (correctWeights == 5) {
    // puzzle is solved
    solve();
  }
}

//called once at start
void setupPuzzles() {
  Wire.begin(); //init I2c communication 

  statusObj["p"][cauldronPuzzle] = 0;
  statusObj["pi"][cauldronPuzzle] = "0,0,0,0,0";

  //define pins
  pinMode(crystalPin, OUTPUT);
  digitalWrite(crystalPin, HIGH);

  startupScales();
  
  sendCloseBox();
}

//reset puzzle state, set all current weights to 0 (tare)
void resetPuzzles() {
  LoadCell_1.tareNoDelay(); 
  LoadCell_2.tareNoDelay(); 
  LoadCell_3.tareNoDelay(); 
  LoadCell_4.tareNoDelay(); 
  LoadCell_5.tareNoDelay(); 
  statusObj["p"][cauldronPuzzle] = 0;
  statusObj["pi"][cauldronPuzzle] = "0,0,0,0,0";

  sendCloseBox();
}

void resetPuzzleById(String puzzleId) {
  //handle resetting specific puzzle based on id
  resetPuzzles();
}

//called every loop
void checkPuzzles() {
  if (statusObj["p"][cauldronPuzzle] = 0) {
    checkSolution();
  }
}

//called when host pc is asking puzzle inputs
void convertPuzzleInputsToString() 
{
  //convert all stored puzzle answers to string
  readValues();
}

//called when operator clears puzzle anwers (not every puzzles has this.)
void clearInput(String puzzleId)
{
  //clear answers from related puzzleId
}