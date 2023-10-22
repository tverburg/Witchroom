void setupCapSense() {
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor init"); 

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }

  cap.setThreshholds(4, 2);

  Serial.println("MPR121 found!");
}

void registerInputs() {
  // Get the currently touched pads
  uint16_t currtouched = cap.touched();
  Serial.println(currtouched);
  
  
  // code that works with only activating the rune
  for (uint8_t i=0; i<numberOfRunes; i++) {
    // check if the runes are not already active and if its touched
    if(!runes[i].active && (currtouched & _BV(i))) {
        Serial.print(i); Serial.println(" touched");

        runes[i].active = true;
        digitalWrite(runePins[i], HIGH);

        activeCounter++;
    }
  }

// code that works with toggling the rune
  // for (uint8_t i=0; i<numberOfRunes; i++) {
  //   // check only if the runes not active or is not in an unresponsive state
  //   if(!runes[i].active || ((currentMillis - runes[i].updated) < unresponsiveTime )) {
  //     // if its touched and not in an unresponsive state
  //     if (currtouched & _BV(i)) {
  //       Serial.print(i); Serial.println(" touched");

  //       runes[i].active = !runes[i].active; // toggle state
  //       runes[i].updated = currentMillis; // save the toggle time

  //       if(runes[i].active) {
  //         activeCounter++;
  //       } else {
  //         activeCounter--;
  //       }
  //     }
  //   }
  // }
  
}