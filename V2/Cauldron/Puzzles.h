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
  //add every puzzle controlled by this controller to status array
  //Example:
  //statusObj["p"]["puzzle id"] = 1; //status op puzzles are saved here
  //statusObj["pi"]["puzzle id"] = "[2, 4, -8, 3, 2]"; //inputs of puzzles are saved here
}

void resetPuzzles() {
  //handle resetting all puzzles
}

void resetPuzzleById(String puzzleId) {
  //handle resetting specific puzzle based on id
}

//called every loop
void checkPuzzles() {
  //handle puzzle stuff here button press etc
}

//called when host pc is asking puzzle inputs
void convertPuzzleInputsToString() 
{
  //convert all stored puzzle answers to string
  //statusObj["pi"][puzzle id] = string puzzle input;
}

//called when operator clears puzzle anwers (not every puzzles has this.)
void clearInput(String puzzleId)
{
  //clear answers from related puzzleId
}