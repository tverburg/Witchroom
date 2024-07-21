//controller config
#define controllerId 4
#define controlerName "cauldron"

//serial config
#define baudRate 115200
#define endMarker  '\n'

//component config
#define boxLock 5

char statusUpdateMessage[64];

pinMode(manualPin, INPUT_PULLUP);
pinMode(crystalPin, INPUT_PULLUP);
pinMode(endStopPin, INPUT_PULLUP);

