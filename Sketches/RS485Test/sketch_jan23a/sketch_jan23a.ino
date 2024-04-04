#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

// constants won't change. Used here to set a pin number:
const int ledPin = LED_BUILTIN;  // the number of the LED pin

// Variables will change:
int ledState = LOW;  // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 1000;  // interval at which to blink (milliseconds)

void setup() {
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);

  Serial.begin(9600);
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);

  Serial.println("setup complete");
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
        Serial.println("led on");
        mySerial.println("led on");
    } else {
      ledState = LOW;
        Serial.println("led off");
        mySerial.println("led off");
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

      if (mySerial.available() > 0) {
        mySerial.read();
    }
}
