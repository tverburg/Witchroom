// ---------------------------------------------------------
// Serial communication include
//
// Used for serial communication with host pc
//
// THIS HAS BEEN PREBUILD DONT TOUCH!!!!
// -------------------------------------------------------

#if hasPuzzles || hasEvents || hasLocks
extern JsonDocument statusObj;
#endif

void setupSerial() {
  Serial.begin(baudRate); // dont touch
}

void checkSerial() {
  if (Serial.available() > 0) {
    String jsonString = Serial.readStringUntil(endMarker); // read string until configured end marker
    jsonString.trim(); // remove end marker
    JsonDocument data;
    DeserializationError error = deserializeJson(data, jsonString);
    //handel deserialization error
    if (error){
      #if useLogging
      logString(F("Json parse error"));// return succesfully update status
      #endif
      return;
    }
    JsonObject messageObj = data.as<JsonObject>();
    if (messageObj.containsKey(F("i"))){
      if (messageObj[F("i")]==controllerId){
        if(messageObj.containsKey(F("a"))){
          if (messageObj[F("a")]==ping){ //check if action is ping
            Serial.println(F("pong"));
          }
          else if (messageObj[F("a")]==resetController) //check if action is resetController 
          {
            Serial.println(F("k"));// return succesfully update status
            //reset all puzzles, effects, events, locks etc
            resetComponents();
          }
          #if hasPuzzles || hasEvents || hasLocks || hasEffects
          else if (messageObj[F("a")]==resetComponent) //check if action is reset component
          {
            //reset specific component
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("i"))&&messageObj[F("d")].containsKey(F("t"))){//check if data object contain i (id), t (type)
                String type = messageObj[F("d")][F("t")];
                String id = messageObj[F("d")][F("i")];

                #if hasPuzzles
                  if (type == F("p"))
                  {
                    resetPuzzleById(id);
                  }
                #endif
                #if hasEvents
                  if (type == F("e"))
                  {
                    resetEventById(id);
                  }
                #endif
                #if hasEffects
                  if (type == F("ef"))
                  {
                    resetEffectById(id);
                  }
                #endif

                Serial.println(F("k"));
              }
            }
          }    
          #endif    
          #if hasPuzzles || hasEvents || hasLocks
          else if (messageObj[F("a")]==statusCheck) { //check if action is statusCheck of puzzles and events
            #if hasPuzzles
            convertPuzzleInputsToString();
            #endif

            //send status json
            serializeJson(statusObj, Serial);
            Serial.print(F("\n"));
          }
          else if (messageObj[F("a")]==updateStatus) { //check if action is updateStatus
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("i"))&&messageObj[F("d")].containsKey(F("t"))&&messageObj[F("d")].containsKey(F("s"))){//check if data object contain i (id), t (type), s (status)
                String type = messageObj[F("d")][F("t")];
                String id = messageObj[F("d")][F("i")];
                int status = messageObj[F("d")][F("s")];
                if(statusObj.containsKey(type)){//check if status object has type
                  if(statusObj[type].containsKey(id)){ //check if type object has id
                    statusObj[type][id] = status; // save new status
                    #if useLogging
                    logString("U"+type+id+"To"+status);
                    #endif
                    Serial.println(F("k"));// return succesfully update status
                  }
                }
              }
            }
          }
          #if hasPuzzles
          else if (messageObj[F("a")]==clearPuzzleInput) { //check if action is updateStatus
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("i"))){//check if data object contain i (id), t (type), s (status)
                String id = messageObj[F("d")][F("i")];
                clearInput(id);

                Serial.println(F("k"));// return succesfully clear puzzle input
              }
            }
          }
          #endif
          #endif

          #if hasEffects
          else if (messageObj[F("a")]==executeSpecial) { //check if action is updateStatus
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("n"))&&messageObj[F("d")].containsKey(F("v"))){//check if data object contain i (id), t (type), s (status)
                String name = messageObj[F("d")][F("n")];
                String value = messageObj[F("d")][F("v")];

                receivedSpecial(name, value);

                Serial.println(F("k"));// return succesfully executed special
              }
            }
          }
          #endif
          #if hasTimer
          else if (messageObj[F("a")]==updateTime) { //check if action is updatetime
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("v"))){//check if data object contain i (id), t (type), s (status)
                String value = messageObj[F("d")][F("v")];

                receivedTime(value);

                Serial.println(F("k"));// return succesfully update time
              }
            }
          }
          #endif

          #if hasHints
          else if (messageObj[F("a")]==displayHint) { //check if action is displayhint
            if(messageObj.containsKey(F("d"))){//check if request object has data
              if(messageObj[F("d")].containsKey(F("v")) && messageObj[F("d")].containsKey(F("t"))){//check if data object contain i (id), t (type), s (status)
                String type = messageObj[F("d")][F("t")];
                String value = messageObj[F("d")][F("v")];

                receivedHint(type, value);

                Serial.println(F("k"));// return succesfully update time
              }
            }
          }
          #endif
          #if useLogging
          else if (messageObj[F("a")]==getControllerLog) { //check if action is updateStatus
            printLogToSerial();
          }
          #endif

          //if command not recognized
          else {
            Serial.println(F("Command not recognized"));
          }
        }
      }
    }
  }
}