
/** Author: Tom van den Bulk
  Sketch voor de kruidenkist schuifpuzzel. Elk puzzelstuk heeft 2 contactpunten oftewel 2 reed switches.
  De schuifpuzzel is een 3 bij 4 bord, met 1 leeg vak, dus 11 vakken met 2 switches een totaal van 22 reed switches.
  ================
  =  0  1  2  3  =
  =  4  X  5  6  =
  =  7  8  9 10  =
  ================
*/
//signal pin to read the state of the reed switches, the mux signal pin.
const int SIG_PIN = 2;
//Signal pin to the electric lock.
const int LOCK_PIN = 6;
//pin to manually control the lock of the puzzle.
const int FAIL_SAFE_PIN = 7;
//Mux control pins
const int s0 = 8;
const int s1 = 9;
const int s2 = 10;
const int s3 = 11;

bool solved = false;
const int numberOfPins = 10;
long time;
long resettime = 60000;

void setup(){
  Serial.begin(9600);
  Serial.println("Setup");
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(FAIL_SAFE_PIN, INPUT_PULLUP);
  pinMode(SIG_PIN, INPUT_PULLUP);
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(LOCK_PIN, LOW);
  
  time = millis();
}

void loop(){
  //not yet solved
  if (!solved){
    //check for manual solve command
    bool failSaveActive = digitalRead(FAIL_SAFE_PIN) == LOW;
    if(failSaveActive){
       Serial.print("manual reset requested");
      //wait for a short period to ensure we've received an actual command and no static
      delay(300);
      //still LOW? activate failsave
      bool failSaveStillActive = digitalRead(FAIL_SAFE_PIN) == LOW;
      if(failSaveStillActive) {
        Serial.print("manual reset activated");
        solve();
      }
    }
    //check for puzzle solve
    else{
      int count = 0;

      for(int i = 0; i < numberOfPins; i ++){ 
        if(readMux(i) == 0){
         Serial.print("1,");
          count++;
        } else {
           Serial.print("0,");
        }
         
        // if all pins are on their correct positions. puzzle is solved
        if(count == numberOfPins){
          solve();
          time = millis();
        }
      }
      Serial.println();
    }
  }
  //if the puzzle is solved. Check every [resettime] milliseconds if it's changed back to an unsolved state
  else{
    if((time + resettime) < millis()){
      int count = 0;
      for(int i = 0; i < numberOfPins; i ++){
        if(readMux(i) == 0){
          count++;
        }
      }
      if(count != numberOfPins){
        solved = false;
      }
      time = millis();
    }
  }
}

void solve(){
  digitalWrite(LOCK_PIN,HIGH); // RELAY ON 
  delay(400);
  digitalWrite(LOCK_PIN,LOW);
  solved = true;
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

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
  int val = digitalRead(SIG_PIN);

  //return the value
  return val;
}

void readValues(){
  Serial.print("Values: ");
    for(int i = 0; i < numberOfPins; i ++){
      Serial.print(i);
      Serial.print(":");
      Serial.print(readMux(i));
      Serial.print(", ");
      delay(100);
    }
    Serial.println();
}
