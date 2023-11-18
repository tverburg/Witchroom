//PIN declarations
const int sigMuxRunePin = 18;
const int r0 = 14;
const int r1 = 15;
const int r2 = 16;
const int r3 = 17;
const int lightPins[] = {2,3,4,5,6,7,8,9,10,11};
const int lockPin = 12;

/*
De muur der Runen bestaat uit 10 runen die verschillende afbeeldingen voorstellen.
De volgorde van de runen startend vanaf rechtsboven en dan met de klok mee. 1.Kruis, 2.Zon, 3.Heks, 4.Maan, 5.Golven, 6.Liefde, 7.Pijl, 8.Oog, 9.Vogel, 10.Ster
De oplossing is een volgorde van 5 opeenvolgende runen die de spelers uit een verhaal moeten halen.(Maan, Zon, Kruis, Heks, Liefde)
*/
struct Rune{
  boolean isActive;
};

const int numberOfLights = 10;
const int numberOfRunes = 10;
Rune runes[numberOfRunes];
const int solutionLength = 5;
const int solution[solutionLength] = {3,1,0,2,5};
boolean resetting = false;
boolean solved = false;
int activeRunes[solutionLength];
int numberOfRunesActive = 0;
long inactiveSeconds = 5000;
long currentTime;

void setup() {
  Serial.begin(9600);

  pinMode(sigMuxRunePin, INPUT_PULLUP);
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(r3, OUTPUT);
  for (int i = 0; i < numberOfLights; i++) {
    pinMode(lightPins[i], OUTPUT);
  }
  pinMode(lockPin, OUTPUT);

  for(int i = 0; i < numberOfRunes; i++){
    runes[i].isActive = false;
  }
  resetLights();
  currentTime = millis();
}

void loop() {
  //printRuneState();
  //if(millis() > currentTime + inactiveSeconds){
  //  currentTime = millis();
  //  resetLights();
  //}

  if (resetting) {
    if (checkIfRunesAreDormant()) {
      resetting = false;
      reset();
      Serial.println("resetting complete, all runes dormant");
    }
  }else{
  //check if puzzle is solved
    if(!solved){
      //check if a rune has been activated;
      for(int i = 0; i < numberOfRunes; i++){

        int value = readMuxRunes(i);

        if(value == 1){
          //if the rune had not been activated yet, set it to active and add to the activeRunes
          if(runes[i].isActive == false){
            runes[i].isActive = true;
            activeRunes[numberOfRunesActive] = i;
            numberOfRunesActive++;
            toggleLight(i+2, HIGH);

            Serial.print("rune: ");
            Serial.print(i);
            Serial.print(" is now active.");
            Serial.print("total of ");
            Serial.print(numberOfRunesActive);
            Serial.print(" active.");
            Serial.println();
          }
        }
      }
      //if 5 runes have been activated check if it is the correct rune order
      if(numberOfRunesActive == solutionLength){
        Serial.println("5 active runes, checking solution");
        checkIfSolved();
      }
    }
  }
}

void toggleLight(int light, int state){
  digitalWrite(light, state);
}

void resetLights(){
  for (int i = 0; i < numberOfLights; i++) {
    toggleLight(i+2, LOW);
  }
}

void checkIfSolved(){
  int correctRunes = 0;
  for(int i = 0; i < solutionLength; i++){
    if(solution[i] == activeRunes[i]){
      correctRunes++;
    }
  }
  if(correctRunes == solutionLength){
    solve();
    Serial.println("solved bitches");
  }
  else{
    resetting = true;
  }
}

void reset(){
  resetLights();
  numberOfRunesActive = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    runes[i].isActive = false;
  }
}

boolean checkIfRunesAreDormant(){
  boolean dormant = false;
  int count = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    if(readMuxRunes(i) == 1){
      count++;
    }
  }
  if(count == 0){
    dormant = true;
  }
  return dormant;
}

void solve(){
  solved = true;
  digitalWrite(lockPin, HIGH);
}

void printRuneState()
{
  Serial.print("cross: ");
  Serial.print(readMuxRunes(0));
  Serial.print(". sun: ");
  Serial.print(readMuxRunes(1));
  Serial.print(", Y: ");
  Serial.print(readMuxRunes(2));
  Serial.print(", moon: ");
  Serial.print(readMuxRunes(3));
  Serial.print(", wave: ");
  Serial.print(readMuxRunes(4));
  Serial.print(", love: ");
  Serial.print(readMuxRunes(5));
  Serial.print(", arrow: ");
  Serial.print(readMuxRunes(6));
  Serial.print(", eye: ");                  
  Serial.print(readMuxRunes(7));
  Serial.print(", bird: ");
  Serial.print(readMuxRunes(8));
  Serial.print(", star: ");
  Serial.print(readMuxRunes(9));
  Serial.println();
}

int readMuxRunes(int channel){
  int controlPin[] = {r0, r1, r2, r3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = digitalRead(sigMuxRunePin);

  //return the value
  return val;
}
