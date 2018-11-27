#include <FastLED.h>

// How many leds are in the strip?
#define DATA_PIN 7
#define NUM_LEDS 100
CRGB leds[NUM_LEDS];

void setup() {
    delay(1000);
    FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(150); } }


// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  // static uint8_t hue = 128;
  // static uint8_t hue = 0;
  // static uint8_t hue = 32;
  static uint8_t hue = 64;
  // FastLED.showColor(CHSV(hue++, 255, 100)); 
  // FastLED.showColor(CHSV(hue++, 128, 100)); 
  // FastLED.showColor(CHSV(hue++, 64, 100)); 
  FastLED.showColor(CHSV(hue++, 128, 100)); 
  fadeall();
  delay(1000);
}