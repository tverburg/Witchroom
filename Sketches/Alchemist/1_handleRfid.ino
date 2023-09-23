// GLOBALS
const byte numReaders = 2;
// reader data pins
const byte ssPins[] = {8, 9};
// Array of MFRC522 instances. one for each reader
MFRC522 mfrc522[numReaders];
// NFC tag ID's required for the puzzle. respectively: {skull, card}
const String correctIDs[] = {"1798219327", "16379217145"};   // card: 19561189148
// the tag IDS currently detected by each reader
String currentIDs[numReaders];

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

bool isPuzzleSolved() {
  // assume the puzzle has been solved
  boolean puzzleSolved = true;

  // assume the tags have not changed since last reading
  boolean changedValue = false;

  Serial.print("isPuzzleSolved | readers: ");
  Serial.println(numReaders);

  // Loop through each reader. 
  // Note: to prevent false negatives or failures because of lost rfid contact the strategy is to remember every last tag ID and not remove it if the tag is removed again. Only the appearence of a new tag wil overwrite the previous value
  // this way the chances or failure due to moing or falling tags is negated. It only increases the chance for false positives which is not necessarily  a bad thing for an escape room puzzle
  for (uint8_t i=0; i<numReaders; i++) {
    Serial.println("point1");
      // init the sensor
      //mfrc522[i].PCD_Init();
Serial.println("point2");
      // Serial.print("init reader ");
      // Serial.println(i);

      // String to hold the ID detected by each sensor
      
Serial.println("point3");
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
          
          // set the flag to show that the puzzle state has changed
          changedValue = true;
          // Update the stored value for this sensor
          currentIDs[i] = readRFID;

          // check if this reading was already stored in the other sensor, if so remove it. Cant have 2 readers triggerd by the same tag
          int opposingID = 1 - i; // flips between 0 and 1
          if (readRFID == currentIDs[opposingID]) {
            currentIDs[opposingID] = "";
          }
        }

              // halt PICC
      mfrc522[i].PICC_HaltA();
      // stop encryption on PCD
      mfrc522[i].PCD_StopCrypto1();
      }
Serial.println("point4");
      // If the reading fails to match the correct ID for this sensor
      if(currentIDs[i] != correctIDs[0] && currentIDs[i] != correctIDs[1]) {
        // the puzzle has not been solved
        puzzleSolved = false;
      }
  }

  Serial.println("done with the loop");

  // if the changedValue flag has been set, at least one sensor has changed
  if(changedValue) {
    Serial.println("somehting chaNged");
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

  Serial.print("return ");
        Serial.println(puzzleSolved);

  return puzzleSolved;
}