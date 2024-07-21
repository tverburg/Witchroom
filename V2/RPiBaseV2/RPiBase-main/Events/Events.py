import Main
from StatusTypes import StatusTypes
from Events import Events

def setupEvents():
    #add every event controlled by this controller to status array
    #Example:
    #Main.status["e"]["event id"] = 1; //status op events are saved here
    #Main.status["es"]["event id"] = "[2, 4, -8, 3, 2]"; //inputs of events are saved here
    Main.status["e"]["1"] = 0
    Main.status["es"]["1"] = 0
    Main.status["e"]["2"] = 0
    Main.status["es"]["2"] = 0

def resetEvents():
    pass #handle resetting all events

def resetEventById(eventId:str):
    pass #handle resetting specific event based on id

#called every loop
def checkEvents():
    pass #handle event stuff here button press etc