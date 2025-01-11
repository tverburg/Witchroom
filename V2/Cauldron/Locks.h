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

void open() {
  enableMotor();
  bool isOpen = openBox();

  if(isOpen) {
    statusObj["l"][boxLockId] = openedlock;
    disableMotor();
  }   
}

void close() {
  enableMotor();
  bool isClosed = closeBox();

  if(isClosed) {
    statusObj["l"][boxLockId] = closedlock;
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

  // check current state of lock.
  uint8_t openStopPinState = digitalRead(openStopPin);
  uint8_t closeStopPinState = digitalRead(closeStopPin);
  if(openStopPinState == LOW) {
    // the box is currently open
    statusObj["l"][boxLockId] = openedlock;
  } else if(closeStopPinState == HIGH) {
    // the box is currently closed
    statusObj["l"][boxLockId] = closedlock;
  } else {
    // the box is in limbo. set it to open as it should be there
    statusObj["l"][boxLockId] = openedlock;
  }
}

void resetLocks() {
  //handle resetting locks
}

//called every loop
void checkLocks(){
  //opening
  if(statusObj["l"][boxLockId] == openinglock) {
    Serial.println("state is opening ");
    open();
  }

  //closing
  if(statusObj["l"][boxLockId] == closinglock) {
    close();
  }
}
      

