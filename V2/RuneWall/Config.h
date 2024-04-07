//controller config
#define controllerId 4
#define controlerName "RuneWall"

//serial config
#define baudRate 1000000
#define endMarker  '\n'

//component config
#define runeWallPuzzle 1
#define openDoorEvent 1

/*
De muur der Runen bestaat uit 10 runen die verschillende afbeeldingen voorstellen.
De volgorde van de runen startend vanaf rechtsboven en dan met de klok mee. 1.Kruis, 2.Zon, 3.Heks, 4.Maan, 5.Golven, 6.Liefde, 7.Pijl, 8.Oog, 9.Vogel, 10.Ster
De oplossing is een volgorde van 5 opeenvolgende runen die de spelers uit een verhaal moeten halen.(Maan, Zon, Kruis, Heks, Liefde)
*/

//PIN declarations
const int sigMuxRunePin = 14; 
const int r0 = 13; //A0
const int r1 = 15; //A1
const int r2 = 16; //A2
const int r3 = 17; //A3
const int lightPins[] = {2,3,4,5,6,7,8,9,10,11};
const int lockPin = 12;

struct Rune{
  boolean isActive;
};

char runesState[22] = "0000000000"; 

const int numberOfLights = 10;
const int numberOfRunes = 10;
Rune runes[numberOfRunes];
const int solutionLength = 5;
const int solution[solutionLength] = {3,1,0,2,5};
boolean resetting = false;
boolean solved = false;
int activeRunes[solutionLength];
int numberOfRunesActive = 0;
long inactiveSeconds = 10000;
long currentTime;