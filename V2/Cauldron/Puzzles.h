// ---------------------------------------------------------
// Puzzles include
//
// Used for controlling puzzles
//
// Use predefined functions below to control all puzzles on controller
// -------------------------------------------------------
extern JsonDocument statusObj;


void solve(){

}

//called once at start
void setupPuzzles() {

}

//reset puzzle state, set all current weights to 0 (tare)
void resetPuzzles() {

}

void resetPuzzleById(String puzzleId) {
  //handle resetting specific puzzle based on id
  resetPuzzles();
}

//called every loop
void checkPuzzles() {

}

//called when host pc is asking puzzle inputs
void convertPuzzleInputsToString() 
{
  //convert all stored puzzle answers to string

}

//called when operator clears puzzle anwers (not every puzzles has this.)
void clearInput(String puzzleId)
{
  //clear answers from related puzzleId
}