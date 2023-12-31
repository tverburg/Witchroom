// buffer to hold the messages to ben sent/have been received
char msg[64];
// The topic to which to subscribe for actions or updates
char listenerTopic[32];
long lastReconnectAttempt = 0;

PubSubClient client(server, 1883, callback, ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(F("Message arrived ["));
  Serial.print(topic);
  Serial.print(F("] "));
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic,subTopics[0])==0){
    //pingrequest
    client.publish(pubTopics[0], "connected");
  }
  else if (strcmp(topic,subTopics[1])==0){
    //solve herbs
    manageHerbs(true);
  } 
  else if (strcmp(topic,subTopics[2])==0){
    // open front door
    manageFrontDoor(true);
  } 
  else if (strcmp(topic,subTopics[3])==0){
    // close front door
    manageFrontDoor(false);
  } 
  else if (strcmp(topic,subTopics[4])==0){
    // activate smoke machine
    manageSmoke(true);
  } 
  else if (strcmp(topic,subTopics[5])==0){
    // deactivate smoke machine
    manageSmoke(false);
  } 
}

boolean reconnect() {
    if (client.connect(deviceID, "shape", "escape")) {
      Serial.println(F("connected. start subscriptions"));
      client.publish(pubTopics[0], "connected");
      // Subscribe to topics meant for this device
      

      for (int i = 0 ; i < numberOfSubscriptions; i++) {
        Serial.print("Subscription for '");
        Serial.print(subTopics[i]);

        bool subscriptionStatus= client.subscribe(subTopics[i], 1);

        if(!subscriptionStatus) {
          Serial.print("' failed!");
        }
        Serial.println(".");
      }

      // Subscribe to topics meant for all devices
      client.subscribe("witchroom/all");
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
  //snprintf(listenerTopic, 32, "%s/%s/control", nameSpace, deviceID);

  Ethernet.begin(mac);

  client.subscribe("witchroom/manage/#");

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
  }
  Ethernet.maintain();
}