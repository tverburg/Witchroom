const uint8_t numberOfLights = 10;
const uint8_t numberOfRunes = 10;
const uint8_t lightPins[] = {2,3,4,5,6,7,8,9,10,11};
const uint8_t runePins[] = {35,37,39,41,43,45,47,49,51,53};
const uint8_t lockPin = 12;

//volatile char runesState[22] = "0,0,0,0,0,0,0,0,0,0:0"; 
char runesState[22] = "0,0,0,0,0,0,0,0,0,0:0"; 


/*
De muur der Runen bestaat uit 10 runen die verschillende afbeeldingen voorstellen.
De volgorde van de runen startend vanaf rechtsboven en dan met de klok mee. 1.Kruis, 2.Zon, 3.Heks, 4.Maan, 5.Golven, 6.Liefde, 7.Pijl, 8.Oog, 9.Vogel, 10.Ster
De oplossing is een volgorde van 5 opeenvolgende runen die de spelers uit een verhaal moeten halen.(Maan, Zon, Kruis, Heks, Liefde)
*/

struct Rune{
  boolean isActive;
  uint8_t pin;
  const char* name;
};


Rune runes[numberOfRunes];
const uint8_t solutionLength = 5;
const uint8_t solution[solutionLength] = {3,1,0,2,5};
boolean resetting = false;
boolean solved = false;
uint8_t activeRunes[solutionLength] = {};
uint8_t numberOfRunesActive = 0;
long inactiveSeconds = 10000;
long currentTime;

void setup() {
  delay(1000);

  Serial.begin(9600);
  Serial.println("init setup");
  
  Serial.println("-- init output pins --");

  for (int i = 0; i < numberOfLights; i++) {
    pinMode(lightPins[i], OUTPUT);
  }
  pinMode(lockPin, OUTPUT);

  Serial.println("-- init input pins --");

  for(int i = 0; i < numberOfRunes; i++){
    runes[i].isActive = false;
    runes[i].pin = runePins[i];
    pinMode(runePins[i], INPUT);
  }

  runes[0].name = "cross";
  runes[1].name = "sun";
  runes[2].name = "Y";
  runes[3].name = "moon";
  runes[4].name = "wave";
  runes[5].name = "love";
  runes[6].name = "arrow";
  runes[7].name = "eye";                  
  runes[8].name = "bird";
  runes[9].name = "star";

  Serial.println("-- done --");

  resetLights();
  currentTime = millis();

  resetting = false;
  solved = false;
  Serial.println("setup done");
}

// void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
  //printRuneState();
  // if(millis() > currentTime + inactiveSeconds){
  //  currentTime = millis();
  //  resetLights();
  // }

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

        int value = readRunes(i);

        //Serial.print("the current value of channel ");
        //Serial.print(i);
        //Serial.print(" is ");
        //Serial.print(value);

        if(value == 1){
          //if the rune had not been activated yet, set it to active and add to the activeRunes
          if(runes[i].isActive == false){
            runes[i].isActive = true;
            activeRunes[numberOfRunesActive] = i;
            numberOfRunesActive++;
            setLight(i+2, HIGH);

            uint8_t runeIndex = i*2; // the locaion of the rune in the statestring is twice the index because of the seperating comma

            noInterrupts();
            runesState[runeIndex] = '1';
             interrupts();

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
      } else if(numberOfRunesActive > solutionLength) {
         Serial.println("too many selected. resetting");
         resetting = true;
      }
     
    }
  }
}

void setLight(int light, int state){
  Serial.print("setLight() ");
  Serial.print(light);
  Serial.print(" to: ");
  Serial.println(state);

  digitalWrite(light, state);
}

void resetLights(){
  for (int i = 0; i < numberOfLights; i++) {
    setLight(i+2, LOW);
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

    uint8_t runeIndex = i*2; // the locaion of the rune in the statestring is twice the index because of the seperating comma
    runesState[runeIndex] = '0';
  }
}

boolean checkIfRunesAreDormant(){
  boolean dormant = false;
  int count = 0;
  for (int i = 0; i < numberOfRunes; i++) {
    if(readRunes(i) == 1){
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

  runesState[20] = '1';
}

void printRuneState()
{
  for(int i = 0; i < numberOfRunes; i++){
    Serial.print(runes[i].name);
    Serial.print(": ");
    Serial.print(readRunesByPin(runes[i].pin));
    Serial.print(", ");
  }
  Serial.println();
}

int readRunes(int index) {
  int val = digitalRead(runePins[index]);

  return val;
}

int readRunesByPin(int pin) {
  int val = digitalRead(pin);

  return val;
}
