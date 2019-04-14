#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    12
#define CLK_PIN     11
#define LED_TYPE    SK9822
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];
byte recv_buffer[NUM_LEDS*3];

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);
  Serial.setTimeout(1000);
}

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  int num = Serial.readBytes(recv_buffer, NUM_LEDS*3);
  if (num == NUM_LEDS*3) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].r = recv_buffer[i*3 + 0];
      leds[i].g = recv_buffer[i*3 + 1];
      leds[i].b = recv_buffer[i*3 + 2];
    }
    FastLED.show();
    Serial.write(0x01);
  } else {
    Serial.write(0x00);
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
