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
   Serial.println(F("start setup RFID"));

  for (uint8_t i=0; i<numReaders; i++){
    // init the reader
    mfrc522[i].PCD_Init(ssPins[i], 9);

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

  Serial.println(F("----- END SETUP RFID -----"));
}

void readRFID() {
  // assume the puzzle has been solved
  boolean puzzleSolved = true;
  // assume the tags have not changed since last reading
  boolean changedValue = false;


  // Loop through each reader
  for (uint8_t i=0; i<numReaders; i++) {
      // init the sensor
      mfrc522[i].PCD_Init();

      // String to hold the ID detected by each sensor
      String readRFID = "";

      // If the sensor detects a tag and is able to read it
      if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
        // extract the ID from the tag
        readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
      }

      // if the current reading is different from the last known reading
      if(readRFID != currentIDs[i]) {
        // set the flag to show that the puzzle state has changed
        changedValue = true;
        // Update the stored value for this sensor
        currentIDs[i] = readRFID;
      }

      // If the reading fails to match the correct ID for this sensor
      if(currentIDs[i] != correctIDs[i]) {
        // the puzzle has not been solved
        puzzleSolved = false;
      }

      // halt PICC
      mfrc522[i].PICC_HaltA();
      // stop encryption on PCD
      mfrc522[i].PCD_StopCrypto1();
  }

  // if the changedValue flag has been set, at least one sensor has changed
  if(changedValue) {
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
      Serial.println(currentIDs[i]);
    }
    Serial.println(F("----"));
  }

  
  // if the puzzlesolved flag is set all sensors detected the correct id
  if(puzzleSolved) {
    //onSolve();
  }
}