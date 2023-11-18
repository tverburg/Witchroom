// Define hardware connections
#define PIN_MOTOR_CONTROL 5 //D1
#define PIN_GATE_IN 4       //D2
#define PIN_ANALOG_IN A0 

// define variables
unsigned long blowStartMillis;  //point in the counter the blow started
unsigned long currentMillis; //current point in the global counter
unsigned long swirlStartMillis; //point in the counter the swirl started
const unsigned long blowPeriod = 100; // amount of time the "blow" needs to take in order for it to be recognized as such. to prevent spikes from yelling or something
const unsigned long swirlPeriod = 10000; // amount of time the "swirling" will take place
boolean swirling = false;
boolean blowing = false;
const double soundTriggerFactor = 1.3;
int baseLevel = 0;
int previousValue = 0;

void setup()
{
  Serial.begin(9600);
  
  // Configure pins as output
  pinMode(PIN_MOTOR_CONTROL, OUTPUT); 
  digitalWrite(PIN_MOTOR_CONTROL, HIGH); 

  //calibrate sensor
  // take a sample of readings from the sensor
  int numSamples = 10;
  int sumReadings = 0;
  for(int i=0; i<numSamples; i++) {
    // Add each reading to the total
    sumReadings += analogRead(PIN_ANALOG_IN);
    delay(100);
  }
  //Calculate mean average of readings taken
  float avgReading = (float)sumReadings / numSamples;
  // use this as the "base" reading;
  baseLevel = avgReading;

  swirling = false;

  // Display status
  Serial.print("Initialized with a baselevel of ");
  Serial.print(baseLevel);
  Serial.print(" and a triggerlevel of ");
  Serial.println(baseLevel*soundTriggerFactor);
}

int smooth(int current, int previous) {
  float f1 = 2.3;
  int f2 = 3;
  float f3 = 0.5;
  int v = ((f1*previous)+(f3*current))/f2;
  return v;
}

int improvedSmooth(int current, int previous) {
  double c = current * 1.0;
  double p = previous * 1.0;
  int total = c+previous;
  Serial.print(total);
  int v = ((p/(total))*p) + ((c/(total))*c);
  Serial.print(", ");
  Serial.print(v);
  Serial.print("_________");
  return v * 1.0; // to double conversion
}

void loop()
{
  currentMillis = millis();
  int value;
  float soundTriggerLevel = baseLevel*soundTriggerFactor;
  
  if(!swirling) {
      digitalWrite(PIN_MOTOR_CONTROL, HIGH); 
    // Check the envelope input
    int currentValue = analogRead(PIN_ANALOG_IN);
    // value = ((currentValue + previousValue)/2); // add a smoothing function
    // value = smooth(currentValue, previousValue);
    value = improvedSmooth(currentValue, previousValue);
    Serial.print(previousValue);
    Serial.print(" -> ");
    Serial.print(currentValue);
    Serial.print(" ->");
    Serial.println(value);


    // Serial.print("value: ");
    // Serial.println(value);
    // Serial.print("currentValue: ");
    // Serial.println(currentValue);

    previousValue = value;

    // if we start blowing, register it and start the counter
    if((value > soundTriggerLevel) && !blowing)
    {
      Serial.println("started blowing");
        blowing = true;
        blowStartMillis = millis();
    } 
    // if we stop blowing, register it
    else if ((value <= soundTriggerLevel) && blowing){
      Serial.println("stopped blowing");
        blowing = false;
    } 
    // if we are blowing for some time, check if we reached the required period
    else if ((value > soundTriggerLevel) && blowing) {
      Serial.println("keep going");
      // if we reached the blow period, start the swirl. reset the start
      if(currentMillis - blowStartMillis >= blowPeriod) {
        Serial.println("enough blowing");
        swirling = true;
        blowing = false;
        swirlStartMillis = millis();
      }
    }
  } 
  else {
    Serial.println("swirling");
    Serial.println(currentMillis - swirlStartMillis);
    
    digitalWrite(PIN_MOTOR_CONTROL, LOW); 

      // if we reached the swirl period, stop the swirl.
      if(currentMillis - swirlStartMillis >= swirlPeriod) {
        Serial.println("stop the swirling!");
        swirling = false;
        blowing = false;
        previousValue = 0;
      }
  }
}