// buffer to hold the messages to ben sent/have been received
char msg[64];
// The topic to which to subscribe for actions or updates
char listenerTopic[32];
char publishingTopic[32];
long lastReconnectAttempt = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(F("Message arrived ["));
  // Serial.print(topic);
  // Serial.print(F("] "));
  // for (int i=0;i<length;i++) {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();

  String topicStr = topic;
  if(topicStr.endsWith("/reset")) 
  {
    Serial.println(F("reset the bastard"));
    reset();
  } 
  else if(topicStr.endsWith("/solve")) 
  {
    Serial.println(F("solve the bastard"));
    solve();
  }

}

PubSubClient client(server, 1883, callback, ethClient);

void subscribe() {
  Serial.println(F("connected. start subscriptions"));

  //char solveTopic[40];
  //snprintf(solveTopic, 40, "%s/%s", listenerTopic, "solve");
  //char updateTopic[40];
  //snprintf(updateTopic, 40, "%s/%s", listenerTopic, "reset");

  //Serial.println(solveTopic);
  //Serial.println(updateTopic);


  client.publish(publishingTopic, "connected");
  // Subscribe to topics meant for this device
  client.subscribe(listenerTopic);
  // Subscribe to topics meant for all devices
  client.subscribe("witchroom/all");
}

boolean reconnect() {
    if (client.connect(deviceID, "shape", "escape")) {
      subscribe();
    } else {
      Serial.println(F("client not connected: "));
      Serial.println(client.state());
    };
  return client.connected();
}

bool valueToBool(int value) {
  if(value == 1) {
    return true;
  } else {
    return false;
  }
}

void mqttEthernetSetup() {
  Serial.println(F("mqttEthernetSetup"));
  //set the topics for this device
  snprintf(listenerTopic, 32, "%s/%s/#", nameSpace, deviceID);
  snprintf(publishingTopic, 32, "%s/%s/msg/", nameSpace, deviceID);

  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
  
  if (client.connect(deviceID, "shape", "escape")) {
   subscribe();
  } else {
    Serial.println(F("client not connected: "));
    Serial.println(client.state());
  };

  lastReconnectAttempt = 0;
};

void mqttLoop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }

}