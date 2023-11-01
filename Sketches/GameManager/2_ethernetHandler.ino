void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

void ethernetSetup()
{
  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
  
  if (client.connect("gameManager", "shape", "escape")) {
    client.publish("witchroom","online");
    client.subscribe("witchroom/game/#");
  }
}

void ethernetLoop()
{
  client.loop();
}
