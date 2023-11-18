// buffer to hold the messages to ben sent/have been received
char msg[64];
// The topic to which to subscribe for actions or updates
char listenerTopic[32];
char publishingTopic[32];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(F("Message arrived ["));
  Serial.print(topic);
  Serial.print(F("] "));
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

PubSubClient client(server, 1883, callback, ethClient);

bool valueToBool(int value) {
  if(value == 1) {
    return true;
  } else {
    return false;
  }
}

void onSolve() {
  //#ifdef DEBUG
    //Serial.println("Puzzle has just been solved");
  //#endif

  // todo: do something with output pin

  // Update the global puzzle state
  puzzleState = Solved;

  // publish message to MQTT broker
  client.publish(publishingTopic, "solved");
}

void onUnSolve() {
  //#ifdef DEBUG
    //Serial.println("Puzzle has just become unsolved");
  //#endif

   // todo: do something with output pin

  // Update the global puzzle state
  puzzleState = Running;

  // publish message to MQTT broker
  client.publish(publishingTopic, "unsolved");
}

void onReset() {
  //#ifdef DEBUG
    //Serial.println(F("Puzzle has just been reset!"));
  //#endif

  // todo: reset the output pin

  // Update the global puzzle state
  puzzleState = Running;

  // publish message to MQTT broker
  client.publish(publishingTopic, "reset");
}

void mqttEthernetSetup() {
  //set the topics for this device
  snprintf(listenerTopic, 32, "%s/%s/control", nameSpace, deviceID);
  snprintf(publishingTopic, 32, "%s/%s/update", nameSpace, deviceID);

  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
  
  if (client.connect(deviceID, "shape", "escape")) {
    client.publish(publishingTopic, "connected");
    // Subscribe to topics meant for this device
    client.subscribe(listenerTopic);
    // Subscribe to topics meant for all devices
    client.subscribe("witchroom/all");
  };
};