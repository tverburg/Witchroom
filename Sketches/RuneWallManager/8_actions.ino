void requestRuneStatus() {
  Wire.requestFrom(runeWallI2cAddress, 21);    // request the status of the runewall 16 bytes from runewall

  char newUpdateMessage[22] = "0,0,0,0,0,0,0,0,0,0:0"; 
  uint8_t i = 0;
  while (Wire.available()) {
    char c = Wire.read(); // receive a byte as character
    // Serial.print(i);
    // Serial.print(c);
    newUpdateMessage[i]=c;
    i++;
  }
  //Serial.println();
  //Serial.print(newUpdateMessage);         

  if(strcmp(updateMessage, newUpdateMessage) == 0) {
    //Serial.print(" is the same as "); 
  } else {
    //Serial.print(" is different than"); 
    Serial.print("new state, pubishing"); 
    client.publish(pubTopics[0], newUpdateMessage);

    if(newUpdateMessage[20] == '1') {
      client.publish(pubTopics[1], ""); // send a solved message
    }
  }

  Serial.println(updateMessage);

  strcpy(updateMessage, newUpdateMessage);
}

void solve() {
  Wire.beginTransmission(runeWallI2cAddress); // transmit to device #4
  Wire.write(1);              // sends one byte. 1 means solve
  Wire.endTransmission();    // stop transmitting
}

void reset() {
  Wire.beginTransmission(runeWallI2cAddress); // transmit to device #4
  Wire.write(0);              // sends one byte. 0 means reset
  Wire.endTransmission();    // stop transmitting
}

void receiveEvent(int action)
{
  int i = 0;
  //updateMessage = "                     ";

  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    updateMessage[i] = c; // save to message

    Serial.print(updateMessage);          // print the character
    i++;
  }

  client.publish(pubTopics[0], updateMessage);
}