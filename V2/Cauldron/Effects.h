// ---------------------------------------------------------
// Effects include
//
// Used for controlling effects
//
// Use predefined functions below to control all effects on controller
// -------------------------------------------------------
#define COOLING  80
#define SPARKING 50

//led color palette
CRGBPalette16 gPal;

const uint8_t NUM_LEDS = 60;
const uint8_t BRIGHTNESS = 200;
const uint8_t FRAMES_PER_SECOND = 60;
bool gReverseDirection = false;
CRGB leds[NUM_LEDS];


//all set to black. lghts are "off"
void makeDark() {
  gPal = CRGBPalette16( CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black);
}

void makeColored() {
  gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
}

void LightAnimationWithPalette()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void ledLoop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  LightAnimationWithPalette(); // run simulation frame, using palette colors
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

//called once at start
void setupEffects(){
  //FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.setBrightness( BRIGHTNESS );
  
  // start with lights off
  makeDark();
}

void resetEffects() {
  //handle resetting effects
  makeDark();
}

void resetEffectById(String effectId) {
  //handle resetting specific effect based on id
}

//called every loop
void checkEffects(){
  //handle effects stuff
  //ledLoop();
}

//called when host pc executes special effect
//name and value for special are passed
//only save data needed for special execute in checkEffects()
void receivedSpecial(String name, String value) {
  //handle receiving special effects
    if(name == "crystallight") {
        if(value == "off") {
            makeDark();
        } else if(value == "on") {
            makeColored();
        }
    }
}