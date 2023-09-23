void setup() {
  Serial.begin(9600);

  setupCapSense();

  // init runes
  for(int i=0; i < numberOfRunes; i++) {
    runes[i].id = i;
    runes[i].active = false;
    runes[i].updated = 0;

    // set the pins default to off
    pinMode(runePins[i], OUTPUT);
    digitalWrite(runePins[i], LOW);
  };

  // init the pins
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, LOW);
};

void loop() {
  currentMillis = millis();

  if(!paused){
    registerInputs();
  } else if((currentMillis - pausedMillis) > unresponsiveTime) {
    // resume input 
    paused = false;
    pausedMillis = 0;
  };

  // to be removed
  debugStuff();

  const bool solved = isPuzzleSolved();

  if(solved) {
    Serial.println("jeej");
  } else {
    // not solved yet
  }
};
