// The alchemist reader is an ESP that handles the RFID reading. 
// It's output pin is set to high if the reader is successfull, and low in all other states 

#include <SPI.h>
#include <MFRC522.h>

// RFID
const byte numReaders = 2;
// reader data pins. SPI connections are on D5 (CLK) D6(MISO) and D7(MOSI)
const byte ssPins[] = {D1, D2};
const int rfidResetPin = D3;
// Array of MFRC522 instances. one for each reader
MFRC522 mfrc522[numReaders];
// NFC tag ID's required for the puzzle. respectively: {skull, card}
const String correctIDs[] = {"24313329149", "19561189148"};   // card: 19561189148
// the tag IDS currently detected by each reader
String currentIDs[numReaders];

uint8_t outputPinA = D8;
uint8_t outputPinB = D4;