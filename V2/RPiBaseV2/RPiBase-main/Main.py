import json
from StatusTypes import StatusTypes

from Logging.Logger import Logger
from Serial.SerialInterface import SerialInterface

with open('Config/Config.json', 'r') as file:
    config = json.load(file)
with open('Config/BuildConfig.json', 'r') as file:
    buildConfig = json.load(file)
    
status = {}

if buildConfig["hasPuzzles"]:
    status["p"] = {}
    status["pi"] = {}
if buildConfig["hasEvents"]:
    status["e"] = {}
    status["es"] = {}
if buildConfig["hasLocks"]:
    status["l"] = {}
    status["ls"] = {}

serialInterface = SerialInterface(config)
logger = Logger()

import Setup
import Reset
from Serial import Serial
from Puzzles import Puzzles
from Effects import Effects
from Hints import Hints
from Locks import Locks
from Timer import Timer
from Events import Events

def setup():
    Setup.setupComponents()
    
def loop():
    if buildConfig["useSerial"]:
        Serial.checkSerial()
    if buildConfig["hasPuzzles"]:
        Puzzles.checkPuzzles()
    if buildConfig["hasEvents"]:
        Events.checkEvents()
    if buildConfig["hasLocks"]:
        Locks.checkLocks()
    if buildConfig["hasEffects"]:
        Effects.checkEffects()
    if buildConfig["hasTimer"]:
        Timer.checkTimer()
    if buildConfig["hasHints"]:
        Hints.checkHints()







try:
    #main guard
    if __name__ == "__main__":
        setup()
        
        while True:
            loop()        

#kill threads in case of keyboard interruption (ctrl ^ c)
except KeyboardInterrupt:
    serialInterface.close()
    raise