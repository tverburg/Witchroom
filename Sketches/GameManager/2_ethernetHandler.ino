// The topic to which to subscribe for actions or updates
char listenerTopic[32];
char publishingTopic[32];

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

PubSubClient client(server, 1883, callback, ethClient);

void ethernetSetup()
{
  Serial.println("ethernetSetup");
  //set the topics for this device
  snprintf(listenerTopic, 32, "%s/%s/control", nameSpace, deviceID);
  snprintf(publishingTopic, 32, "%s/%s/update", nameSpace, deviceID);

  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
  
  if (client.connect("gameManager", "shape", "escape")) {
    Serial.println("connected");
    client.publish("witchroom","online");
    client.subscribe("witchroom/game/#");
  } else {
    Serial.print("not connected");
    Serial.println(client.state());
  }
}

void ethernetLoop()
{
  client.loop();
}
