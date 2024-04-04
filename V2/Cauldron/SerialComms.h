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
      logString("Json parse error");// return succesfully update status
      return;
    }
    JsonObject messageObj = data.as<JsonObject>();
    if (messageObj.containsKey("i")){
      if (messageObj["i"]==controllerId){
        if(messageObj.containsKey("a")){
          if (messageObj["a"]==ping){ //check if action is ping
            Serial.println("pong");
          }
          else if (messageObj["a"]==resetController) //check if action is resetController 
          {
            //reset all puzzles, effects, events, locks etc
            resetComponents();
          }
          #if hasPuzzles || hasEvents || hasLocks || hasEffects
          else if (messageObj["a"]==resetComponent) //check if action is reset component
          {
            //reset specific component
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("i")&&messageObj["d"].containsKey("t")){//check if data object contain i (id), t (type)
                String type = messageObj["d"]["t"];
                String id = messageObj["d"]["i"];

                #if hasPuzzles
                  if (type == "p")
                  {
                    resetPuzzleById(id);
                  }
                #endif
                #if hasEvents
                  if (type == "e")
                  {
                    resetEventById(id);
                  }
                #endif
                #if hasEffects
                  if (type == "ef")
                  {
                    resetEffectById(id);
                  }
                #endif

                Serial.println('k');
              }
            }
          }    
          #endif    
          #if hasPuzzles || hasEvents || hasLocks
          else if (messageObj["a"]==statusCheck) { //check if action is statusCheck of puzzles and events
            #if hasPuzzles
            convertPuzzleInputsToString();
            #endif

            //send status json
            serializeJson(statusObj, Serial);
            Serial.print("\n");
          }
          else if (messageObj["a"]==updateStatus) { //check if action is updateStatus
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("i")&&messageObj["d"].containsKey("t")&&messageObj["d"].containsKey("s")){//check if data object contain i (id), t (type), s (status)
                String type = messageObj["d"]["t"];
                String id = messageObj["d"]["i"];
                int status = messageObj["d"]["s"];
                if(statusObj.containsKey(type)){//check if status object has type
                  if(statusObj[type].containsKey(id)){ //check if type object has id
                    statusObj[type][id] = status; // save new status
                    logString("U"+type+id+"To"+status);
                    Serial.println('k');// return succesfully update status
                  }
                }
              }
            }
          }
          #if hasPuzzles
          else if (messageObj["a"]==clearPuzzleInput) { //check if action is updateStatus
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("i")){//check if data object contain i (id), t (type), s (status)
                String id = messageObj["d"]["i"];
                clearInput(id);

                Serial.println('k');// return succesfully update status
              }
            }
          }
          #endif
          #endif

          #if hasEffects
          else if (messageObj["a"]==executeSpecial) { //check if action is updateStatus
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("n")&&messageObj["d"].containsKey("v")){//check if data object contain i (id), t (type), s (status)
                String name = messageObj["d"]["n"];
                String value = messageObj["d"]["v"];

                receivedSpecial(name, value);

                Serial.println('k');// return succesfully executed special
              }
            }
          }
          #endif
          #if hasTimer
          else if (messageObj["a"]==updateTime) { //check if action is updatetime
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("v")){//check if data object contain i (id), t (type), s (status)
                String value = messageObj["d"]["v"];

                receivedTime(value);

                Serial.println('k');// return succesfully update time
              }
            }
          }
          #endif

          #if hasHints
          else if (messageObj["a"]==displayHint) { //check if action is displayhint
            if(messageObj.containsKey("d")){//check if request object has data
              if(messageObj["d"].containsKey("v") && messageObj["d"].containsKey("t")){//check if data object contain i (id), t (type), s (status)
                String type = messageObj["d"]["t"];
                String value = messageObj["d"]["v"];

                receivedHint(type, value);

                Serial.println('k');// return succesfully update time
              }
            }
          }
          #endif
          #if useLogging
          else if (messageObj["a"]==getControllerLog) { //check if action is updateStatus
            Serial.println(totalLogString);
            totalLogString = "";
          }
          #endif

          //if command not recognized
          else {
            Serial.println("Command not recognized");
          }
        }
      }
    }
  }
}