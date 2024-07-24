// ---------------------------------------------------------
// Locks include
//
// Used for controlling locks
//
// Use predefined functions below to control all locks on controller
// -------------------------------------------------------

extern JsonDocument statusObj;

static boolean lockOpening = false;
static int time = 0;
const int openTime = 4000;

bool openBox() {
  uint8_t endStopState = digitalRead(openStopPin); 
  bool opened = (endStopState == LOW);

  if(!opened){
    // Set the spinning direction counterclockwise
    digitalWrite(dirPin, HIGH);

    turnMotor();
  }

  return opened;
}

// Start closing the box. returns true while closing. false if finished
bool closeBox() {
  uint8_t endStopState = digitalRead(closeStopPin); 
  bool closed = (endStopState == HIGH);

  if(!closed){
    // Set the spinning direction counterclockwise
    digitalWrite(dirPin, LOW);

    turnMotor();
  }

  return closed;
}

void enableMotor() {
  digitalWrite(enableMotorPin, LOW); // enable motor driver
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(resetPin, HIGH); 
}

void disableMotor() {
  digitalWrite(enableMotorPin, HIGH); // disable motor driver
  digitalWrite(sleepPin, LOW); 
  digitalWrite(resetPin, LOW); 
}

void turnMotor() {
  // Spin the stepper motor enough revolutions to move 1/3 of the box:
  for (int i = 0; i < steps; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepperSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepperSpeed);
  }
  
}

void open() {
  //makeRed();
  //statusObj["es"][boxLightsEffectId] == "1";

  enableMotor();
  bool isOpen = openBox();

  if(isOpen) {
    statusObj["l"][boxLockId] = openedlock;
    disableMotor();
  }   
}

void close() {
  //makeBlue();
  //statusObj["es"][boxLightsEffectId] == "0";

  enableMotor();
  bool isClosed = closeBox();

  if(isClosed) {
    statusObj["l"][boxLockId] = closedlock;
    disableMotor();
  }   
}


//called once at start
void setupLocks(){
  //set motor and endstop pins
  pinMode(openStopPin, INPUT_PULLUP);
  pinMode(closeStopPin, INPUT_PULLUP);
  pinMode(resetPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);

  // enable motor so the box cant be openend manually
  enableMotor();

  statusObj["l"][boxLockId] = openlock; //status op locks are saved here

  // open box on start
  open();
}

void resetLocks() {
  //handle resetting locks
  open();
}

//called every loop
void checkLocks(){
  //opening
  if(statusObj["l"][boxLockId] = openinglock;) {
    Serial.println("state is opening ");
    open();
  }

  //closing
  if(statusObj["l"][boxLockId] = closinglock;) {
    close();
  }
}
      

