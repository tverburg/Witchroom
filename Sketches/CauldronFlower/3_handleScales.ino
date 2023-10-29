void setupScales() {
  Serial.println(F("Setup scales"));
  tare();
  Serial.println(F("Done tare"));
}

void tare() {
  bool tareSuccessful = false;

  unsigned long tareStartTime = millis();
  while (!tareSuccessful && millis()<(tareStartTime+TARE_TIMEOUT_SECONDS*1000)) {
    tareSuccessful = scales.tare(20,10000);  //reject 'tare' if still ringing
  }
}

void sendRawData() {
  scales.read(results);
  for (int i=0; i<scales.get_count(); ++i) {;
    Serial.println( -results[i]);  
    //Serial.print( (i!=scales.get_count()-1)?"\t":"\n");
  }  
  delay(10);
}