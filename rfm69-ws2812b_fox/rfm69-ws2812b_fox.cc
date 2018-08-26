// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include <FastLED.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 100
#define HUE 100.0

// Data pin that led data will be written out over
#define DATA_PIN 7

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
// CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;

// This function sets up the ledsand tells the controller about them
void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

      // Uncomment one of the following lines for your leds arrangement.

      FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   //  static uint8_t hue;
   // // Move a single white led 
   //  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
   //    // Turn our current led on to white, then show the leds
   //    leds[whiteLed] = CHSV(hue++,255,255);

   //    // Show the leds (only one of which is set to white, from above)
   //    FastLED.show();
      
   //    // Wait a little bit
   //    delay(300);
      

   //    // Turn our current led back to black for the next loop around
   //    leds[whiteLed] = CRGB::Black;
   //    fadeall();

   //  }
   //  for(int whiteLed = (NUM_LEDS)-1; whiteLed >= 0; whiteLed = whiteLed -1) {
   //        // Turn our current led on to white, then show the leds
   //    leds[whiteLed] = CRGB::Orange;
   //    FastLED.show();

   //    // Wait a little bit
   //    delay(100);

   //    // Turn our current led back to black for the next loop around
   //    leds[whiteLed] = CRGB::Black;
   // }
    static uint8_t HUE;
  for(int i = 0; i < NUM_LEDS; i++) {   
    // fade everything out
    leds.fadeToBlackBy(80);

    // let's set an led value
    leds[60] = CHSV(HUE,255,255);

    // now, let's first 20 leds to the top 20 leds, 
    // leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(45);
  }

}