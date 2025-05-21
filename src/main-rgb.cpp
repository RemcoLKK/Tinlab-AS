#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN         48
#define NUMPIXELS   1
#define FADE_DELAY  10   // ms between color-steps; lower = faster

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.show();  // initialize all pixels to “off”
}

void loop() {
  // sweep pos from 0→255 across the color wheel
  for (uint16_t pos = 0; pos < 256; pos++) {
    pixels.setPixelColor(0, wheel(pos));
    pixels.show();
    delay(FADE_DELAY);
  }
  // if you want it to reverse smoothly, uncomment:
  // for (int16_t pos = 255; pos >= 0; pos--) {
  //   pixels.setPixelColor(0, wheel(pos));
  //   pixels.show();
  //   delay(FADE_DELAY);
  // }
}

// ---------------------------------------------------------------------------
// wheel()
//    Input: 0–255 index on the color wheel
//    Returns: 32-bit RGB color that smoothly transitions
// ---------------------------------------------------------------------------
uint32_t wheel(uint8_t pos) {
  if (pos < 85) {
    // red up, green down
    return pixels.Color(pos * 3, 255 - pos * 3, 0);
  }
  else if (pos < 170) {
    // green up, blue down
    pos -= 85;
    return pixels.Color(255 - pos * 3, 0, pos * 3);
  }
  else {
    // blue up, red down
    pos -= 170;
    return pixels.Color(0, pos * 3, 255 - pos * 3);
  }
}
