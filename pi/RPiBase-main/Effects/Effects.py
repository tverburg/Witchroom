import Main
from Effects import Effects

def setupEffects():
    #setup effect stuf here
    pass

def resetEffects():
    pass #handle resetting all effects

def resetEffectById(effectId:str):
    pass #handle resetting specific effect based on id

#called every loop
def checkEffects():
    pass #handle effect stuff here button press etc

#called when host pc executes special effect
#name and value for special are passed
#only save data needed for special execute in checkEffects()
def receivedSpecial(name, value):
    pass #handle receiving special