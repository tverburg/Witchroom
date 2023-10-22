bool valueToBool(int value) {
  if(value == 1) {
    return true;
  } else {
    return false;
  }
}

void reconnect() {
  Serial.println(F("reconnect..."));
  // Loop until we're reconnected
  while (!MQTTclient.connected()) {
    Serial.print(F("Attempting MQTT connection with id: "));
    Serial.print(deviceID);
    //Serial.print(F("... "));
    // Attempt to connect
    if (MQTTclient.connect(deviceID)) {
      Serial.println(F("MQTT connected"));
      // Once connected, publish an announcement...
      publish("'cabin door' is connected");
      // ... and resubscribe
      MQTTclient.subscribe(topic);
      // Subscribe to topics meant for all devices
      MQTTclient.subscribe("witchroom/all");
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(MQTTclient.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttLoop() {
  if (!MQTTclient.connected()) {
    reconnect();
  }
  MQTTclient.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print(F("Message arrived ["));
  //Serial.print(topic);
  //Serial.print(F("] "));
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  //Serial.println();
}

void onSolve() {
  //#ifdef DEBUG
    //Serial.println("Puzzle has just been solved");
  //#endif

  // todo: do something with output pin

  // Update the global puzzle state
  puzzleState = Solved;

  // publish message to MQTT broker
  publish("Test puzzle solved!");
}

void onUnSolve() {
  //#ifdef DEBUG
    //Serial.println("Puzzle has just become unsolved");
  //#endif

   // todo: do something with output pin

  // Update the global puzzle state
  puzzleState = Running;

  // publish message to MQTT broker
  publish("Test puzzle unsolved!");
}

void onReset() {
  //#ifdef DEBUG
    //Serial.println(F("Puzzle has just been reset!"));
  //#endif

  // todo: reset the output pin

  // Update the global puzzle state
  puzzleState = Running;

  // publish message to MQTT broker
  publish("Test puzzle reset!");
}

void mqttSetup() {
  // Define some settings for the MQTT client
  MQTTclient.setClient(ethernetClient);
  MQTTclient.setServer(mqttServerIP, 1883);
  //MQTTclient.setCallback(callback);
  snprintf(topic, 32, "witchroom/puzzles/%s", deviceID);
}

void ethernetSetup() {
  // Attempt to connect to the specified network
  Serial.print(F("Connecting to the network with ip "));
  Serial.println(deviceIP);

  //Ethernet.begin(mac, deviceIP);

  //if(Ethernet.begin(mac) == 0) {
 //   Serial.println(F("Ethernet configuration using DHCP failed"));
 //   for(;;);
  //}

  // First, try to create a DHCP connection
  if (Ethernet.begin(mac) == 0) {
    // Try to connect using specified IP address instead of DHCP
    Ethernet.begin(mac, deviceIP);
  }

  // give the ethernet shield a couple of seconds to initialize
  //delay(2000);

  // Print debug info about the connection
  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
}

void mqttEthernetSetup() {
  // setup the ethernet connection
  ethernetSetup();
  // setup the MQTT service
  mqttSetup();
}

void initPuzzleStates() {
  // do any puzzle init actions here like calibrations
}

void publish(char* message) {
  Serial.print(F("publishing: "));
  Serial.println(message);
    Serial.println(topic);
  MQTTclient.publish(topic, message);
}