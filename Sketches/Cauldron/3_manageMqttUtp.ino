// buffer to hold the messages to ben sent/have been received
char msg[64];
long lastReconnectAttempt = 0;

PubSubClient client(server, 1883, callback, ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print(F("Message arrived ["));
  // Serial.print(topic);
  // Serial.print(F("] "));
  // for (int i=0;i<length;i++) {
  //   Serial.print((char)payload[i]);
  // }
  //Serial.println();

  // if (strcmp(topic,"witchroom/all/pingRequest")==0){
  //   //pingrequest
  //   client.publish(pubTopics[0], "connected");
  // }
  // else if (strcmp(topic,"witchroom/puzzles/cauldron/solve")==0){
  //   //solve the puzzle
  //   Serial.println(F("solve the bastard"));
  //   solve();
  // } 
  // else if (strcmp(topic,"witchroom/puzzles/cauldron/reset")==0){
  //   // reset the puzzle
  //   Serial.println(F("reset the bastard"));
  //   reset();
  // } 
}

const char deviceId[] = "cauldron";
const char user[] = "shape";
const char pwd[] = "escape";
const char subAll[] = "witchroom/all";

boolean reconnect() {
  Serial.println(F("attempt MQTT connection"));
    if (client.connect(deviceId, user, pwd)) {
      Serial.println(F("connected. start subscriptions"));
      //client.publish(pubTopics[0], "connected");

      // Subscribe to topics meant for this device
      // "witchroom/all/pingRequest"
      // "witchroom/puzzles/cauldron/solve"
      // "witchroom/puzzles/cauldron/reset"

      // Subscribe to topics meant for all devices
      client.subscribe(subAll);    
  //client.subscribe("witchroom/manage/#");

    } else {
      Serial.println(F("client not connected: "));
      Serial.println(client.state());
    };
  return client.connected();
}

void mqttEthernetSetup() {
  Serial.println(F("mqttEthernetSetup"));

  client.setKeepAlive( 90 );

  Ethernet.begin(mac);
  
  // print your local IP address:
  // Serial.print(F("My IP address: "));
  // Serial.println(Ethernet.localIP());

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
  // Ethernet.maintain();
}