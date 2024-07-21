import Main
from Puzzles import Puzzles

def setupPuzzles():
    #add every puzzle controlled by this controller to status array
    #Example:
    #Main.status["p"]["puzzle id"] = 1; //status op puzzles are saved here
    #Main.status["pi"]["puzzle id"] = "[2, 4, -8, 3, 2]"; //inputs of puzzles are saved here
    Main.status["p"]["1"] = 0
    Main.status["pi"]["1"] = ""
    Main.status["p"]["2"] = 0
    Main.status["pi"]["2"] = ""
    Main.status["p"]["4"] = 0
    Main.status["pi"]["4"] = ""

def resetPuzzles():
    pass #handle resetting all puzzles

def resetPuzzleById(puzzleId:str):
    pass #handle resetting specific puzzle based on id

#called every loop
def checkPuzzles():
    pass #handle puzzle stuff here button press etc

def convertPuzzleInputsToString():
    pass
    #convert all stored puzzle answers to string
    #status["pi"][puzzle id] = string puzzle input;
    
def clearInput(puzzleId:str):
    pass #clear answers from related puzzleId