# ---------------------------------------------------------
# Serial communication include
#
# Used for serial communication with host pc
#
# THIS HAS BEEN PREBUILD DONT TOUCH!!!!
# -------------------------------------------------------\
import Main, Reset, Setup
from Puzzles import Puzzles
from Effects import Effects
from Hints import Hints
from Locks import Locks
from Timer import Timer
from Events import Events    
from Serial.SerialInterface import SerialInterface
from Serial.ActionTypes import ActionTypes
import json
    
def checkSerial():
    
    message = Main.serialInterface.checkForMessage()
    if (message != ""):
        try:
            messageJson = json.loads(message)
        except Exception:
            return

        if "i" in messageJson:
            if messageJson["i"] == Main.config["controller"]["controllerId"]:
                if "a" in messageJson:
                    if messageJson["a"]==ActionTypes.ping: #check if action is ping
                        Main.serialInterface.writeStringToSerial("pong")
                    
                    elif messageJson["a"]==ActionTypes.resetController: #check if action is resetController 
                        #reset all puzzles, effects, events, locks etc
                        print("resetting")
                        Main.serialInterface.writeStringToSerial("k")
                        Reset.resetComponents()
                                        
                    elif messageJson["a"]==ActionTypes.resetComponent: #check if action is reset component
                        #reset specific component
                        if "d" in messageJson:#check if request object has data
                            if "i" in messageJson["d"] and "t" in messageJson["d"]:#check if data object contain i (id), t (type)
                                type = messageJson["d"]["t"]
                                id = messageJson["d"]["i"]

                                if type == "p":
                                    Puzzles.resetPuzzleById(id)
                                if type == "e":
                                    Events.resetEventById(id)
                                if type == "ef":
                                    Effects.resetEffectById(id)
                        
                        Main.serialInterface.writeStringToSerial("k")
                            
                    elif messageJson["a"]==ActionTypes.statusCheck: #check if action is statusCheck of puzzles and events
                        if Main.buildConfig["hasPuzzles"]:
                            Puzzles.convertPuzzleInputsToString()

                        jsonString = json.dumps(Main.status, separators=(',', ':'))
                        
                        Main.serialInterface.writeStringToSerial(jsonString)
                    
                    elif messageJson["a"]==ActionTypes.updateStatus: #check if action is updateStatus
                        if"d" in messageJson:#check if request object has data
                            if "i" in messageJson["d"] and "t" in messageJson["d"] and "s" in messageJson["d"]:#check if data object contain i (id), t (type), s (status)
                                type = messageJson["d"]["t"]
                                id = messageJson["d"]["i"]
                                newStatus = messageJson["d"]["s"]
                                if type in Main.status:#check if status object has type
                                    if id in Main.status[type]: #check if type object has id
                                        Main.status[type][id] = newStatus; # save new status
                                        Main.logger.logString("Updated "+type+id+" To "+str(newStatus));
                                        Main.serialInterface.writeStringToSerial('k');# return succesfully update status                   
                                        
                    elif messageJson["a"]==ActionTypes.clearPuzzleInput: #check if action is updateStatus
                        if "d" in messageJson:#check if request object has data
                            if "i" in messageJson["d"]:#check if data object contain i (id), t (type), s (status)
                                id = messageJson["d"]["i"]
                                Puzzles.clearInput(id)

                                Main.serialInterface.writeStringToSerial('k');# return succesfully update status
                            
                    elif messageJson["a"]==ActionTypes.executeSpecial: #check if action is updateStatus
                        if "d" in messageJson:#check if request object has data
                            if "n" in messageJson["d"] and "v" in messageJson["d"]:#check if data object contain i (id), t (type), s (status)
                                name = messageJson["d"]["n"]
                                value = messageJson["d"]["v"]

                                Effects.receivedSpecial(name, value)

                                Main.serialInterface.writeStringToSerial('k');# return succesfully executed special
                        
                    elif messageJson["a"]==ActionTypes.updateTime: #check if action is updatetime
                        if "d" in messageJson:#check if request object has data
                            if "v" in messageJson["d"]:#check if data object contain i (id), t (type), s (status)
                                value = messageJson["d"]["v"]

                                Timer.receivedTime(value)

                                Main.serialInterface.writeStringToSerial('k');# return succesfully update time
                        
                    elif messageJson["a"]==ActionTypes.displayHint: #check if action is displayhint
                        if "d" in messageJson:#check if request object has data
                            if "t" in messageJson["d"] and "v" in messageJson["d"]:#check if data object contain i (id), t (type), s (status)
                                type = messageJson["d"]["t"]
                                value = messageJson["d"]["v"]

                                Hints.receivedHint(type, value)

                                Main.serialInterface.writeStringToSerial('k');# return succesfully display hint
                        
                    elif messageJson["a"]==ActionTypes.getControllerLog: #check if action is updateStatus
                        Main.serialInterface.writeStringToSerial(Main.logger.totalLogString)
                        Main.logger.totalLogString = ""
                    
                    else:
                        Main.serialInterface.writeStringToSerial("Command not recognized")
                        