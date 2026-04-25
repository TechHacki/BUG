#include <Adafruit_NeoPixel.h>

#define LED_PIN    25
#define NUM_LEDS   1

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ================= BASIC =================

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

// ================= PATTERNS =================

// 🔴 Solid Color
void solid(uint8_t r, uint8_t g, uint8_t b, int duration) {
  setColor(r, g, b);
  delay(duration);
}

// 💓 Breathing Effect
void breathing(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 255; i += 5) {
    pixel.setBrightness(i);
    setColor(r, g, b);
    delay(10);
  }
  for (int i = 255; i > 0; i -= 5) {
    pixel.setBrightness(i);
    setColor(r, g, b);
    delay(10);
  }
}

// ⚡ Blink
void blink(uint8_t r, uint8_t g, uint8_t b, int times, int speedDelay) {
  for (int i = 0; i < times; i++) {
    setColor(r, g, b);
    delay(speedDelay);
    setColor(0, 0, 0);
    delay(speedDelay);
  }
}

// 🌈 Rainbow (for 1 LED)
uint32_t wheel(byte pos) {
  pos = 255 - pos;
  if (pos < 85) return pixel.Color(255 - pos * 3, 0, pos * 3);
  if (pos < 170) {
    pos -= 85;
    return pixel.Color(0, pos * 3, 255 - pos * 3);
  }
  pos -= 170;
  return pixel.Color(pos * 3, 255 - pos * 3, 0);
}

void rainbowCycle(int speedDelay) {
  for (int j = 0; j < 256; j++) {
    pixel.setPixelColor(0, wheel(j));
    pixel.show();
    delay(speedDelay);
  }
}

// 🚨 SOS Pattern
void sos() {
  for (int i = 0; i < 3; i++) blink(255,0,0,1,150); // short
  delay(300);
  for (int i = 0; i < 3; i++) blink(255,0,0,1,400); // long
  delay(300);
  for (int i = 0; i < 3; i++) blink(255,0,0,1,150); // short
}

// 🔵 Pulse (quick fade)
void pulse(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 255; i += 15) {
    pixel.setBrightness(i);
    setColor(r, g, b);
    delay(5);
  }
  pixel.setBrightness(255);
}

// ================= SETUP =================

void setup() {
  pixel.begin();
  pixel.setBrightness(50);
  pixel.show();
}

// ================= LOOP =================

void loop() {

  // 🔵 STATUS STYLE (useful for product)
  
  solid(0, 0, 255, 1000);       // Blue = Idle
  
  breathing(0, 255, 0);         // Green = Active
  
  blink(255, 255, 0, 3, 200);   // Yellow = Warning
  
  pulse(0, 255, 255);           // Cyan pulse
  
  rainbowCycle(10);             // RGB cycle
  
  sos();                        // Alert mode
  
  solid(255, 0, 0, 1000);       // Red = Error
}