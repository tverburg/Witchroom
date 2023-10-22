uint8_t sensorPin = 9;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue =  digitalRead(sensorPin);

  Serial.println(sensorValue);

  delay(200);
}
