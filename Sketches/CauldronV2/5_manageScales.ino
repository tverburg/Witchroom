void startupScales(){
  LoadCell_1.begin();
  LoadCell_2.begin();
  LoadCell_3.begin();
  LoadCell_4.begin();
  LoadCell_5.begin();

  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  byte loadcell_1_rdy = 0;
  byte loadcell_2_rdy = 0;
  byte loadcell_3_rdy = 0;
  byte loadcell_4_rdy = 0;
  byte loadcell_5_rdy = 0;
  while ((loadcell_1_rdy + loadcell_2_rdy + loadcell_3_rdy + loadcell_4_rdy + loadcell_5_rdy) < 5) { //run startup, stabilization and tare, both modules simultaniously
    if (!loadcell_1_rdy) loadcell_1_rdy = LoadCell_1.startMultiple(stabilizingtime, _tare);
    if (!loadcell_2_rdy) loadcell_2_rdy = LoadCell_2.startMultiple(stabilizingtime, _tare);
    if (!loadcell_3_rdy) loadcell_3_rdy = LoadCell_3.startMultiple(stabilizingtime, _tare);
    if (!loadcell_4_rdy) loadcell_4_rdy = LoadCell_4.startMultiple(stabilizingtime, _tare);
    if (!loadcell_5_rdy) loadcell_5_rdy = LoadCell_5.startMultiple(stabilizingtime, _tare);
  }
  if (LoadCell_1.getTareTimeoutFlag()) {
    Serial.println(F("Timeout, check MCU>HX711 no.1 wiring and pin designations"));
  }
  if (LoadCell_2.getTareTimeoutFlag()) {
    Serial.println(F("Timeout, check MCU>HX711 no.2 wiring and pin designations"));
  }
  if (LoadCell_3.getTareTimeoutFlag()) {
    Serial.println(F("Timeout, check MCU>HX711 no.3 wiring and pin designations"));
  }
  if (LoadCell_4.getTareTimeoutFlag()) {
    Serial.println(F("Timeout, check MCU>HX711 no.4 wiring and pin designations"));
  }
  if (LoadCell_5.getTareTimeoutFlag()) {
    Serial.println(F("Timeout, check MCU>HX711 no.5 wiring and pin designations"));
  }
  LoadCell_1.setCalFactor(calibrationValue_1); 
  LoadCell_2.setCalFactor(calibrationValue_2); 
  LoadCell_3.setCalFactor(calibrationValue_3); 
  LoadCell_4.setCalFactor(calibrationValue_4); 
  LoadCell_5.setCalFactor(calibrationValue_5); 
  Serial.println(F("Startup is complete"));
}

void readValues(){
  //Serial.println(F("readValues()"));
  static boolean newDataReady = 0;
  const int serialPrintInterval = 1000; //increase value to slow down serial print activity
  
  // check for new data/start next conversion:
  if (LoadCell_1.update()) newDataReady = true;
  LoadCell_2.update();
  LoadCell_3.update();
  LoadCell_4.update();
  LoadCell_5.update();

  //get smoothed value from data set
  if ((newDataReady)) {
    if (millis() > t + serialPrintInterval) {
      int a = LoadCell_1.getData();currentWeights[0] = a;
      int b = LoadCell_2.getData();currentWeights[1] = b;
      int c = LoadCell_3.getData();currentWeights[2] = c;
      int d = LoadCell_4.getData();currentWeights[3] = d;
      int e = LoadCell_5.getData();currentWeights[4] = e;
      // Serial.print("Load_cell 1 output val: ");
      //Serial.print(a);
      // Serial.print(F(","));
      // Serial.print("    Load_cell 2 output val: ");
      //Serial.print(b);
      //Serial.print(F(","));
      // Serial.print("    Load_cell 3 output val: ");
      //Serial.print(c);
      //Serial.print(F(","));
      // Serial.print("    Load_cell 4 output val: ");
      //Serial.print(d);
      //Serial.print(F(","));
      // Serial.print("    Load_cell 5 output val: ");
      //Serial.println(e);

      char statusUpdateMessage[27] = {};
      uint8_t s = solved ? 1 : 0;
      sprintf(statusUpdateMessage,"%d,%d,%d,%d,%d:%d",a,b,c,d,e,s);
      Serial.println(statusUpdateMessage);
      client.publish(pubMsg, statusUpdateMessage);

      newDataReady = 0;
      t = millis();
    }
  }
}

