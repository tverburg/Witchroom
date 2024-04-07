// ---------------------------------------------------------
// Puzzles include
//
// Used for controlling puzzles
//
// Use predefined functions below to control all puzzles on controller
// -------------------------------------------------------
extern JsonDocument statusObj;

void checkIfSolved(){
  int correctRunes = 0;
  for(int i = 0; i < solutionLength; i++){
    if(solution[i] == activeRunes[i]){
      correctRunes++;
    }
  }
  if(correctRunes == solutionLength){
    //puzzle is solved
    statusObj["p"][runeWallPuzzle] = 1;
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

    uint8_t runeIndex = i; // the locaion of the rune in the statestring is twice the index because of the seperating comma
    runesState[runeIndex] = '0';
  }
}

//called once at start
void setupPuzzles() {
  //add every puzzle controlled by this controller to status array
  statusObj["p"][runeWallPuzzle] = 0; //status op puzzles are saved here
  statusObj["pi"][runeWallPuzzle] = "0000000000"; //inputs of puzzles are saved here

  //init pins
  pinMode(sigMuxRunePin, INPUT);
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(r3, OUTPUT);
  for (int i = 0; i < numberOfLights; i++) {
    pinMode(lightPins[i], OUTPUT);
  }

  // set all runes to off at init
  for(int i = 0; i < numberOfRunes; i++){
    runes[i].isActive = false;
  }
  resetLights();
  currentTime = millis();

  resetting = false;
  solved = false;
}

void resetPuzzles() {
  reset();
}

void resetPuzzleById(String puzzleId) {
  reset();
}

//called every loop
void checkPuzzles() {
  if (resetting) {
    if (checkIfRunesAreDormant()) {
      resetting = false;
      reset();
    }
  } else {
  //check if puzzle is solved
    if (!solved) {
      //check if a rune has been activated;
      for(int i = 0; i < numberOfRunes; i++){

        int value = readMuxRunes(i);

        if (value == 1) {
          //if the rune had not been activated yet, set it to active and add to the activeRunes
          if (runes[i].isActive == false) {
            runes[i].isActive = true;
            activeRunes[numberOfRunesActive] = i;
            numberOfRunesActive++;
            toggleLight(i+2, HIGH);

            uint8_t runeIndex = i*2; // the locaion of the rune in the statestring is twice the index because of the seperating comma

            // todo: check if activated rune is correct or not. for now just say active
            // isRune Correct()
            runesState[runeIndex] = '1';
          }
        }
      }

      //if 5 runes have been activated check if it is the correct rune order
      if (numberOfRunesActive == solutionLength) {
        checkIfSolved();
      }
    }
  }
}

//called when host pc is asking puzzle inputs
void convertPuzzleInputsToString() 
{
  statusObj["pi"][runeWallPuzzle] = runesState;
}

//called when operator clears puzzle anwers (not every puzzles has this.)
void clearInput(String puzzleId)
{
  //clear answers from related puzzleId
}