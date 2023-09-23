//input vibration sensor
const byte sensorPin = A0;
// driven low when correct knock is entered
const byte lockPin = 12; 

// knock patern array records the gap *between* knocks so it only has numKnocksInPattern-1 elements
// delays are all normalised to the range 0-1024. so the longest delay in the pattern is always 1024
// and all other delays are expressed as fractions of that

// "shave and a haircut, two bits"
// const int numKnocksInPattern = 7 ;
// const int secretKnockPattern[numKnocksInPattern-1] = {512, 256, 256, 512, 1024, 512};

// "In the air tonight" drum solo
// const int numKnocksInPattern = 10 ;
// const int secretKnockPattern[numKnocksInPattern-1] = {512, 1024, 512, 1024, 512, 1024, 512, 1024, 1024};

// "happy birthday to you"
const int numKnocksInPattern = 6;
const int secretKnockPattern[numKnocksInPattern-1] = {683, 341, 1024, 1024, 1024};

// the amount by which the sensor reading must deviate from its base value to register a knock
// increasing the threshold will make the sensor less sensitive, decreasing will make it more sensitive
const int sensorThreshold = 15;
// if the (normalised) delay between any two knocks in the input sequence deviates by more than this amount compared
// to the correct sequence, the input will be rejected
const int knockErrorTolerance = 128;
// if the average (normalised) delay between all knocks in the input sequence deviates by more than this amount compared
// to the correct sequence, the input will be rejected
const int averageKnockErrorTolerance = 128;
// In order to reduce the risk of detecting erroneous "double-knocks" during input, this specifies a delay (in ms)
// before reading the sensor again
// Fastest I can knock is around 480BPM = 0.125secs between knocks. 400BPM = 0.15secs. 300 BPMN = 0.2secs
const int minGapBetweenKnocks = 125;
// The maximum gap after a knock (in ms) before the pattern is assumed to be finished
const int maxGapBetweenKnocks = 1500;

// GLOBALS
// The base reading of the sensor from which knocks will be measured
// this value will be calibrated based on an average reading taken in setup()
int baseReading = 512;
// The input pattern of knocks entered by the player
int inputPattern[numKnocksInPattern-1];


void setup() {
  Serial.begin(9600);
  Serial.println(F("Entering Setup"));

  // configure pins
  pinMode(sensorPin, INPUT);
  pinMode(lockPin, OUTPUT);

  // init lock
  digitalWrite(lockPin, LOW);

  //calibrate sensor
  // take a sample of readings from the sensor
  int numSamples = 10;
  int sumReadings = 0;
  for(int i=0; i<numSamples; i++) {
    // Add each reading to the total
    sumReadings += analogRead(sensorPin);
    delay(100);
  }
  //Calculate mean average of readings taken
  float avgReading = (float)sumReadings / numSamples;
  // use this as the "base" reading;
  baseReading = avgReading;

  Serial.println(F("Setup done"));
}

void loop() {
  // has there been a (first) knock
  if(knockDetected()) {
    // continue listening for further knocks
    listenToKnockPattern();

    //debug
    Serial.println(F("inputPattern before normalisation"));
    printPattern(inputPattern);

    // the knock has finished, so we first normalise the pattern
    normaliseKnockPattern(inputPattern);

    //debug
    Serial.println(F("inputPattern after normalisation"));
    printPattern(inputPattern);
    Serial.println(F("Correct pattern"));
    printPattern(secretKnockPattern);

    // Knock entered matched the stored pattern
    if(comparePattern(inputPattern,secretKnockPattern)) {
      onPuzzleSolved();
    } else {
      onIncorrectInput();
    }
  }
}

//player enters incorrect pattern
void onIncorrectInput() {
  Serial.println(F("input did not match"));
}

//player enters incorrect pattern
void onPuzzleSolved() {
  Serial.println(F("input matched"));

  //unlock the lock
  digitalWrite(lockPin, HIGH);
  delay(500);
  //cut power again
  digitalWrite(lockPin, LOW);
}

//returns true if a knock is detected
bool knockDetected(){
  int knockSensorValue = analogRead(sensorPin);
  if(abs(knockSensorValue - baseReading) > sensorThreshold) {
    return true;
  } else {
    return false;
  }
}

// Listens for and records the timings of an input knock sequence
void listenToKnockPattern() {
  int lastKnockTime = millis();
  int now = millis();

  Serial.print(F("Knock1"));

  knockDelay();

  // reset the input pattern array
  memset(inputPattern, 0, sizeof(inputPattern));

  //how many knocks in total have been entered in this sequence
  // (note that there must have been one already received in order to know a pattern was being input)
  int currentKnockNumber = 1;

  // wait to hear if there's another knock heard in this sequence
  while((now - lastKnockTime < maxGapBetweenKnocks) && (currentKnockNumber < numKnocksInPattern)) {
    //record the current time
    now = millis();

    // has there been a new knock received?
    if(knockDetected()) {
        Serial.print(F("Knock2"));

        // record the time elapsed since the previous knock
        inputPattern[currentKnockNumber-1] = now - lastKnockTime;
        // Increment the knock counter
        currentKnockNumber++;
        // and update the time a which last knock was received
        lastKnockTime = now;

        knockDelay();
    }
  }
  Serial.println();
}

// compares two normalises knock patterns
// Returns true if the patterns match within given tolerance, or false otherwise
bool comparePattern(int inputPattern[], int secretKnockPattern[]) {
  // TEST#1: has it got the correct number of knocks?
  for(int i=0; i< numKnocksInPattern-1; i++){
    if(inputPattern[i] == 0) {
      Serial.print(F("TEST #1 failed. Input pattern had"));
      Serial.print(i+1);
      Serial.print(F(" knocks. Secret pattern has "));
      Serial.print(numKnocksInPattern);
      Serial.println(F(" Knocks."));
      return false;
    }
  }

  // This variable records the total timing difference between patterns
  int totalDelta = 0;

  // TEST#2: Is the delay between any two successive knocks in the sequence outside the allowed tolerance?
  for( int i=0; i<numKnocksInPattern-1; i++){
    int knockDelta = abs(inputPattern[i] - secretKnockPattern[i]);
    if(knockDelta > knockErrorTolerance) {
      Serial.print(F("TEST #2 failed. Input pattern had delay after knock #"));
      Serial.print(i+1);
      Serial.print(F(" of "));
      Serial.print(inputPattern[i]);
      Serial.print(F(". Secret pattern has "));
      Serial.print(secretKnockPattern[i]);
      Serial.println(F("."));
      return false;
    }
    totalDelta += knockDelta;
  }

  // TEST#3: Is the whole pattern too sloppy
  if (totalDelta / numKnocksInPattern > averageKnockErrorTolerance) {
      Serial.print(F("TEST #3 failed. Input pattern had average timing error of "));
      Serial.print(totalDelta / numKnocksInPattern);
      Serial.print(F(". Secret pattern had"));
      Serial.print(averageKnockErrorTolerance);
      Serial.println(F("ms."));
      return false;
  }

  // If we get to here, all tests have passed
  return true;
}

//Scales the length of delays between knocks in an input pattern to a normalised range of values
// This allows us to compare the rhythem of knock patterns irrespective of the tempo at which they were entered
void normaliseKnockPattern(int knockPattern[]){
  //Keep track of the longest interval in the pattern
  int maxKnockInterval = 0;

  //Loop through the pattern
  for(int i=0; i<numKnocksInPattern-1; i++){
    //Keep track of the longest gap between knocks
    if( knockPattern[i] > maxKnockInterval) {
      maxKnockInterval = knockPattern[i];
    }
  }
  
  //Normalize the pattern by scaling all readings from 0-1024
  for(int i=0; i<numKnocksInPattern-1; i++){
    //Because arrays are passed by reference, changing the value here will change the value in the global variable
    knockPattern[i] = map(knockPattern[i], 0, maxKnockInterval, 0, 1024);
  }
}

void printPattern(int pattern[]){
  for(int i=0;i<numKnocksInPattern-1;i++) {
    Serial.print(pattern[i]);
    // print a comma after all but the last value
    if(i<numKnocksInPattern-2) {
      Serial.print(", ");
    }
  }
  Serial.println("");
}

// handles delay between listening to knocks, allowing peak reading to diminish before listening to next knock
void knockDelay(){
  //rather then simple delay like delay(minGapBetweenKnocks)
  // we'll break the delay into sall chunks, reading the sensor pin each time to try to clear out any erroneous readings caused by capacitance
  int iterations = (minGapBetweenKnocks /10);
  for(int i=0; i<iterations; i++){
    delay(10);
    analogRead(sensorPin);
  }
}