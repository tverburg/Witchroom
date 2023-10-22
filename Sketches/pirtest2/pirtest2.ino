const uint8_t sensorPin = 4;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
}

void loop() {
  const uint8_t sensorValue = digitalRead(sensorPin);

  if(sensorValue == 0) {
    Serial.println("Nothing");
  } else {
    Serial.println("Movement!!");
  }

  delay(200);
}
