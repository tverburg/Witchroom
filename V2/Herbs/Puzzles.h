// ---------------------------------------------------------
// Puzzles include
//
// Used for controlling puzzles
//
// Use predefined functions below to control all puzzles on controller
// -------------------------------------------------------
extern JsonDocument statusObj;

//called once at start
void setupPuzzles() {
  //init pins for mux reading
  pinMode(SIG_PIN, INPUT_PULLUP);
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  //set lock to closed as default
  digitalWrite(LOCK_PIN, LOW);

  //track time for reset game check todo: check if it needs to be removed because the control computer will handle this
  //time = millis();

  //add every puzzle controlled by this controller to status array
  statusObj["p"][herbsPuzzleId] = deactivated; //status of puzzle
  statusObj["pi"][herbsPuzzleId] = "0000000000"; //puzzle input
}

void resetPuzzles() {
  statusObj["p"][herbsPuzzleId] = deactivated;
}

void resetPuzzleById(String puzzleId) {
  resetPuzzles();
}

//called every loop
void checkPuzzles() {
  //not yet solved
  if (statusObj["p"][herbsPuzzleId] == activated) {
    //check for puzzle solve
    int count = 0;

    for(int i = 0; i < numberOfPins; i ++){
      int herbStatus = readMux(i);

      herbsStatusses[i] = !herbStatus; // flip it, because the mux returns 0 for on and 1 for off. The controlSoftware will expect the opposite

      if(herbStatus == 0){
        count++;
      }
      // if all pins are on their correct positions. puzzle is solved
      if(count == numberOfPins){
        //The puzzle is solved
        statusObj["p"][herbsPuzzleId] = completed; 
      //  time = millis();
      }
    }
  }
  //if the puzzle is solved. Check every [resettime] milliseconds if it's changed back to an unsolved state
  //else {
  //  if ((time + resettime) < millis()) {
  //    int count = 0;
  //   for (int i = 0; i < numberOfPins; i ++) {
  //      if (readMux(i) == 0) {
  //        count++;
  //      }
  //    }
  //    if (count != numberOfPins) {
  //      statusObj["p"][herbsPuzzleId] = 0;
  //    }
  //    time = millis();
  //  }
  //}
}

//called when host pc is asking puzzle inputs
void convertPuzzleInputsToString() 
{
  //convert all stored puzzle answers to string
  statusObj["pi"][herbsPuzzleId] = convertIntArrayToString(herbsStatusses, 10);
}

//called when operator clears puzzle anwers (not every puzzles has this.)
void clearInput(String puzzleId)
{
  //not implemented for herbs
}