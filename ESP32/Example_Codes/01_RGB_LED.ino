#include <Adafruit_NeoPixel.h>

#define LED_PIN   45     // RGB Pin
#define NUM_LEDS  1      // Change if more LEDs

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ===================== SETUP =====================
void setup() {
  strip.begin();
  strip.show(); // Initialize OFF
}

// ===================== LOOP =====================
void loop() {

  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue

  rainbowCycle(5);

  breathing(255, 0, 255); // Purple

  blinkColor(255, 255, 0, 300); // Yellow blink
}

// ===================== FUNCTIONS =====================

// Color wipe
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Blink
void blinkColor(int r, int g, int b, int delayTime) {
  for(int i=0; i<5; i++) {
    strip.fill(strip.Color(r, g, b));
    strip.show();
    delay(delayTime);
    strip.clear();
    strip.show();
    delay(delayTime);
  }
}

// Breathing effect
void breathing(int r, int g, int b) {
  for(int i=0; i<255; i++) {
    float brightness = (sin(i * 0.05) + 1) / 2;
    strip.fill(strip.Color(r * brightness, g * brightness, b * brightness));
    strip.show();
    delay(10);
  }
}

// Rainbow cycle
void rainbowCycle(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<NUM_LEDS; i++) {
      int pixelHue = firstPixelHue + (i * 65536L / NUM_LEDS);
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}