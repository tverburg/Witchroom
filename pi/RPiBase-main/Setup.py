import Main
from Puzzles import Puzzles
from Effects import Effects
from Hints import Hints
from Locks import Locks
from Timer import Timer
from Events import Events

def setupComponents():
    if Main.buildConfig["hasPuzzles"]:
        Puzzles.setupPuzzles()
    if Main.buildConfig["hasEvents"]:
        Events.setupEvents()
    if Main.buildConfig["hasLocks"]:
        Locks.setupLocks()
    if Main.buildConfig["hasEffects"]:
        Effects.setupEffects()
    if Main.buildConfig["hasTimer"]:
        Timer.setupTimer()
    if Main.buildConfig["hasHints"]:
        Hints.setupHints()