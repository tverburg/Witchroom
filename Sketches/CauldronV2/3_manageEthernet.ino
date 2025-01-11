void callback(char* topic, byte* payload, unsigned int length) {
  // Serial.print(F("Message arrived ["));
  // Serial.print(topic);
  // Serial.print(F("] "));
  // for (int i=0;i<length;i++) {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();

  if (strcmp(topic,subPing)==0){
    //pingrequest
    client.publish(pubPing, "");
  }
  else if (strcmp(topic,subSolve)==0){
    //solve the puzzle
    //Serial.println(F("solve the bastard"));
    solve();
  } 
  else if (strcmp(topic,subreset)==0){
    // reset the puzzle
    //Serial.println(F("reset the bastard"));
    reset();
  } 
}

void subscribe(const char* subTopic) {
  Serial.print(F("Subscription for '"));
  Serial.print(subTopic);

  bool subscriptionStatus= client.subscribe(subTopic, 1);
                  
  if(!subscriptionStatus) {
    Serial.print(F("' failed!"));
  }
  Serial.println(F("."));
}

boolean reconnect() {
  Serial.println(F("attempt MQTT connection"));
    if (client.connect(deviceId, user, pwd)) {
      Serial.println(F("connected. start subscriptions"));
      // client.publish(pubTopics[0], "connected");

      // Subscribe to topics meant for this device
      subscribe(subPing);
      subscribe(subSolve);
      subscribe(subreset);
      // Subscribe to topics meant for all devices
      subscribe(subAll);

    } else {
      Serial.println(F("client not connected: "));
      Serial.println(client.state());
    };
  return client.connected();
}

void mqttEthernetSetup() {
  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);

  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("Ethernet cable is not connected."));
  }

  delay(1500);
  lastReconnectAttempt = 0;
  reconnect();
  // Serial.println(F("mqttEthernetSetup"));

  // client.setKeepAlive( 90 );

  // Ethernet.begin(mac);
  
  // // print your local IP address:
  // Serial.print("My IP address: ");
  // Serial.println(Ethernet.localIP());

  // //client.subscribe("witchroom/manage/#");

  // lastReconnectAttempt = 0;
};

void mqttLoop()
{
      //   Serial.print(ethClient.connected());
      // Serial.print(F(", "));
      // Serial.println(ethClient.available());

  // manage mqtt connection
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;

      //manage ethernet connection
      // if the server's disconnected, stop the client:
      if (!ethClient.connected()) {
        // Serial.println();
        Serial.println(F("disconnecting."));
        ethClient.stop();

        //client.setClient(ethClient);
        
        Ethernet.begin(mac, ip);
        delay(1000);
      }

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