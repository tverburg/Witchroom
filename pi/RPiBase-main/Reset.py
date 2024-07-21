import Main
from Puzzles import Puzzles
from Effects import Effects
from Hints import Hints
from Locks import Locks
from Timer import Timer
from Events import Events

def resetComponents():
    if Main.buildConfig["hasPuzzles"]:
        Puzzles.resetPuzzles()
    if Main.buildConfig["hasEvents"]:
        Events.resetEvents()
    if Main.buildConfig["hasLocks"]:
        Locks.resetLocks()
    if Main.buildConfig["hasEffects"]:
        Effects.resetEffects()
    if Main.buildConfig["hasTimer"]:
        Timer.resetTimer()
    if Main.buildConfig["hasHints"]:
        Hints.resetHints()