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
#define NUM_LEDS    300
#define BRIGHTNESS  25
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
// #define UPDATES_PER_SECOND 900
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
// bool glitter_state = false;
// bool garland_on_off = true;
// byte dnom = 100;




// extern CRGBPalette16 myRedWhiteBluePalette;
// extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
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


// Define Radio
RFM69 radio;
bool 	readyToXmit = false;
int 	msgSize = 0;


void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
        
    uint8_t brightness = 255;

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    // add glitter based on boolean
    if (sysState.chanceOfGlitter != 0) {
      addGlitter(sysState.chanceOfGlitter);
    }

}


void setup()  {
  delay( 3000 ); // power-up safety delay
  Serial.begin(115200);

  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);
  // WS2811 SETUP
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  
  // currentPalette = RainbowColors_p;
  currentPalette = PartyColors_p;  

  currentBlending = LINEARBLEND;
  // WS2811 END
  sysState.ledsOn = true;
  sysState.updatesPerSecond = 1;
  sysState.ledsBrightness = 128;
  sysState.chanceOfGlitter = 0;
  // set initial led brightness (1-255)
  FastLED.setBrightness(  sysState.ledsBrightness );


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
            // garland_on_off = true;
          break;
          case midnightBlue:
            currentPalette = CloudColors_p;           
            currentBlending = LINEARBLEND;
            // garland_on_off = true;
          break;
          case candyCane:
            currentPalette = myCandyCane_p;
            currentBlending = LINEARBLEND;
            // garland_on_off = true;
          break;
          case Xmas:
            currentPalette = Xmas_p;
            currentBlending = LINEARBLEND;
            // garland_on_off = true;
          break;

          // case fire:
          // break;
          // case fireBurst:
          // break;
          // case patternName_here:
          // break;
          // case patternName_here:
          // break;
          // case glitter_on:
          //   sysState.glitter = true;
          // break;
          // case glitter_off:
          //   sysState.glitter = false;
          // break;
          // case garlandOff:
          //   garland_on_off = false;
          // break;
        }
      break;
      case brightnessCtrl:
        // Change the brightnes of the LEDS
        Sensor_brightnessCtrl = *(_Sensor_brightnessCtrl*)nodeMsg.MsgPayload;
        // Serial.println(Sensor_brightnessCtrl.brightnessNum);

        // sysState.ledsBrightness = floor(255*(Sensor_brightnessCtrl.brightnessNum/100));
        // sysState.calc = Sensor_brightnessCtrl.brightnessNum/100;
        // Serial.println(sysState.calc);
        sysState.ledsBrightness = 255*(Sensor_brightnessCtrl.brightnessNum/100);

        // Serial.println(sysState.ledsBrightness);
        FastLED.setBrightness(  sysState.ledsBrightness );

      break;
      case speedCtrl:
        // Change the speed of the LEDS
        Sensor_speedCtrl = *(_Sensor_speedCtrl*)nodeMsg.MsgPayload;

        sysState.updatesPerSecond = (Sensor_speedCtrl.speedNum/10)+1;
        // Serial.println(sysState.updatesPerSecond);
      break;
      case glitterCtrl:
        Sensor_glitterCtrl = *(_Sensor_glitterCtrl*)nodeMsg.MsgPayload;
        sysState.chanceOfGlitter = Sensor_glitterCtrl.chanceOfGlitter;

      break;
      case resetDefaults:
        sysState.ledsBrightness = 128;
        FastLED.setBrightness(  sysState.ledsBrightness );
        sysState.updatesPerSecond = 1;
      break;


    }
  }

  // ChangePalettePeriodically();
  
  if (sysState.ledsBrightness != 0) {

    static uint8_t startIndex = 0;
    startIndex = startIndex + sysState.updatesPerSecond; /* motion speed */

    
    FillLEDsFromPaletteColors( startIndex);
    

    FastLED.show();
    // FastLED.delay(1000/60);
  }
} // END LOOP



