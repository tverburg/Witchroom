import Main
from Locks import Locks
from StatusTypes import StatusTypes

def setupLocks():
    #add every lock controlled by this controller to status array
    #Example:
    #Main.status["l"]["lock id"] = 1; //status op locks are saved here
    #Main.status["ls"]["lock id"] = "[2, 4, -8, 3, 2]"; //inputs of locks are saved here
    pass

def resetLocks():
    pass #handle resetting all locks

#called every loop
def checkLocks():
    pass #handle lock stuff here button press etc