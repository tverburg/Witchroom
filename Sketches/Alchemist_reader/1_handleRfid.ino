
String dump_byte_array(byte *buffer, byte bufferSize) {
  String uid;
  
  for (byte i = 0; i < bufferSize; i++) {
      /* Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);      */        
      uid += buffer[i] < 0x10 ? " 0" : "";
      uid += buffer[i];
  }

  return uid;
}

void setupRFID() {
  Serial.println(F("setupRFID"));
    SPI.begin();

  for (uint8_t i=0; i<numReaders; i++){
    Serial.print(F("check reader "));
    Serial.println(i);

     Serial.print(F("init reader on "));
    Serial.print(ssPins[i]);
    Serial.print(F(", rst on "));
    Serial.println(rfidResetPin);

    // init the reader
    mfrc522[i].PCD_Init(ssPins[i], rfidResetPin);

    // dump some debug info
    Serial.print(F("Reader #"));
    Serial.print(i);
    Serial.print(F(" initialised on pin "));
    Serial.print(String(ssPins[i]));
    Serial.print(F(". Antenna strength: "));
    Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Version: "));
    mfrc522[i].PCD_DumpVersionToSerial();

    // slight delay before activating next reader
    delay(100);
  }

  Serial.println(F("----- END SETUP -----"));
}

uint8_t isPuzzleSolved() {
  boolean puzzleSolved = false;
  uint8_t correctCount = 0;
  uint8_t state = 0; 

  // assume the tags have not changed since last reading
  boolean changedValue = false;

  // Loop through each reader. 
  // Note: to prevent false negatives or failures because of lost rfid contact the strategy is to remember every last tag ID and not remove it if the tag is removed again. Only the appearence of a new tag wil overwrite the previous value
  // this way the chances or failure due to moing or falling tags is negated. It only increases the chance for false positives which is not necessarily  a bad thing for an escape room puzzle
  for (uint8_t i=0; i<numReaders; i++) {
      // init the sensor
      mfrc522[i].PCD_Init();
      // Serial.print("init reader ");
      // Serial.println(i);

      // String to hold the ID detected by each sensor
      
      // Serial.print("PICC_IsNewCardPresent: ");
      // Serial.print(mfrc522[i].PICC_IsNewCardPresent());
      // Serial.print(", ");
      //  Serial.print("PICC_ReadCardSerial: ");
      // Serial.println(mfrc522[i].PICC_ReadCardSerial());
      

      // If the sensor detects a tag and is able to read it
      if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
        String readRFID = "";
        Serial.print("we have tag from id ");
        Serial.print(i);
        // extract the ID from the tag
        readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);

      Serial.print(", readRFID: ");
      Serial.println(readRFID);

        // if the current reading is different from the last known reading
        if(readRFID != currentIDs[i]) {
          Serial.println("this reading is different");
          // set the flag to show that the puzzle state has changed
          changedValue = true;
          // Update the stored value for this sensor
          currentIDs[i] = readRFID;

          // check if this reading was already stored in the other sensor, if so remove it. Cant have 2 readers triggerd by the same tag
          int opposingID = 1 - i; // flips between 0 and 1
           Serial.print("is ");
           Serial.print(readRFID);
           Serial.print(" the same as ");
           Serial.print(currentIDs[opposingID]);
           Serial.print(" :");
            Serial.println(readRFID == currentIDs[opposingID]);
          if (readRFID == currentIDs[opposingID]) {
            currentIDs[opposingID] = "";
            correctCount--;
          }
        }

              // halt PICC
      mfrc522[i].PICC_HaltA();
      // stop encryption on PCD
      mfrc522[i].PCD_StopCrypto1();
      }

      // If the reading fails to match the correct ID for this sensor
      if(currentIDs[i] == correctIDs[0] || currentIDs[i] == correctIDs[1]) {
        correctCount++;
      }

      //bool correct = 

      // update the information about the state of the readers for any listeners 
      //state += int()
  }

 


  if(correctCount == 2){
// the puzzle has not been solved
    puzzleSolved = true;
  }

  // if the changedValue flag has been set, at least one sensor has changed
  if(changedValue) {
    Serial.println("somehting changed");

    // Dump to serial the current state of all sensors
    for (uint8_t i=0; i<numReaders; i++){
      // init the reader
      mfrc522[i].PCD_Init(ssPins[i], 9);

      // dump some debug info
      Serial.print(F("Reader #"));
      Serial.print(String(i));
      Serial.print(F(" on pin "));
      Serial.print(String(ssPins[i]));
      Serial.print(F(". detected tag: "));
      Serial.println(currentIDs[i]);;   
    }
    Serial.println(F("----"));

    Serial.print("puzzleSolved: ");
    Serial.println(puzzleSolved);
  } 

  return state;
}