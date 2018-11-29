// xmas tree LED lights
#include <RFM69.h>
#include <SPI.h>
// #include <GatewayMsg.h> // Load Gateway Message structure:Task
#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
#include <FastLED.h>
// WS2811 Constants
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    200
#define BRIGHTNESS  25
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 60
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
bool glitter_state = false;
bool garland_on_off = true;
uint8_t brightness = 255;
uint8_t speed = 255;




extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

const TProgmemPalette16 myCandyCane_p PROGMEM =
{
  CRGB::Green,
  CRGB::Green, 
  CRGB::Green,
  CRGB::Green,

  CRGB::Gray,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Gray,

  CRGB::Green,
  CRGB::Green, 
  CRGB::Green,
  CRGB::Green,

  CRGB::Gray,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Gray,
};

const TProgmemPalette16 Xmas_p PROGMEM =
{
  CRGB::Green,
  CRGB::Green, 
  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,

  CRGB::Green,
  CRGB::Green, 
  CRGB::Green,
  CRGB::Green,

  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
};



// Define Radio
RFM69 radio;
bool 	readyToXmit = false;
int 	msgSize = 0;

// void rainbow() {
//   // FastLED's built-in rainbow generator
//   fill_rainbow( leds, NUM_LEDS, gHue, 7);
// }

void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

// void rainbowWithGlitter() {
//   // built-in FastLED rainbow, plus some random sparkly glitter
//   rainbow();
//   addGlitter(80);
// }
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
        
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    // add glitter based on boolean
    if (glitter_state) {
      addGlitter(50);
    }

}


void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        // if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        // if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        // if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        // if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

void setup()  {
  delay( 3000 ); // power-up safety delay


  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);
  // WS2811 SETUP
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  // currentPalette = RainbowColors_p;
  currentPalette = PartyColors_p;  

  currentBlending = LINEARBLEND;
  // WS2811 END
}  // END SETUP

void loop() {
  // Process incoming message / action
  if (radio.receiveDone() ) {
    // Convert radiio data to sensor message
    nodeMsg = *(_NodeMsg*)radio.DATA;
    switch(nodeMsg.TypeID) {
      case patternCtrl:
        // Get Msg Payload Content
        Sensor_patternCtrl = *(_Sensor_patternCtrl*)nodeMsg.MsgPayload;
        switch(Sensor_patternCtrl.patternNum) {
          case rainbows:
          currentPalette = RainbowColors_p;
          currentBlending = LINEARBLEND;
          garland_on_off = true;
          break;
          case midnightBlue:
          currentPalette = CloudColors_p;           
          currentBlending = LINEARBLEND;
          garland_on_off = true;
          break;
          case candyCane:
          currentPalette = myCandyCane_p;
          currentBlending = LINEARBLEND;
          garland_on_off = true;
          break;
          case Xmas:
          currentPalette = Xmas_p;
          currentBlending = LINEARBLEND;
          garland_on_off = true;

          break;

          // case fire:
          // break;
          // case fireBurst:
          // break;
          // case patternName_here:
          // break;
          // case patternName_here:
          // break;
          case glitter_on:
          glitter_state = true;
          break;
          case glitter_off:
          glitter_state = false;
          break;
          case garlandOff:
            garland_on_off = false;
          break;
        }
      break;
      case brightnessCtrl:
      // Change the brightnes of the LEDS
      Sensor_brightnessCtrl = *(_Sensor_brightnessCtrl*)nodeMsg.MsgPayload;
      brightnes = 255*(Sensor_brightnessCtrl.brightnessNum/100);
      break;
      case speedCtrl:
      // Change the speed of the LEDS
      Sensor_speedCtrl = *(_Sensor_speedCtrl*)nodeMsg.MsgPayload;
      speed = 255*(Sensor_speedCtrl.speedNum/100);

      break;

    }
  }

  // ChangePalettePeriodically();
  
  if (garland_on_off) {

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
} // END LOOP

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};


