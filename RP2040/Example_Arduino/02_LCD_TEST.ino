#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// ===== PIN CONFIG =====
#define TFT_DC   8
#define TFT_CS   9
#define TFT_RST  12
#define TFT_BL   13

#define TFT_SCLK 10
#define TFT_MOSI 11

// ===== DISPLAY OBJECT =====
Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// 🔥 BGR FIX
uint16_t colorBGR(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Init display
  tft.initR(INITR_MINI160x80);   // 🔥 IMPORTANT
  tft.setRotation(1);            // Landscape
  tft.invertDisplay(true);       // Fix colors

  tft.fillScreen(colorBGR(0,0,0));
}

// ================= LOOP =================
void loop() {

  colorTest();
  delay(1000);

  gradientTest();
  delay(1000);

  lineTest();
  delay(1000);

  shapeTest();
  delay(1000);

  textTest();
  delay(2000);
}

// ================= TEST FUNCTIONS =================

// 🎨 Solid Colors
void colorTest() {
  uint16_t colors[] = {
    colorBGR(255,0,0),
    colorBGR(0,255,0),
    colorBGR(0,0,255),
    colorBGR(255,255,0),
    colorBGR(0,255,255),
    colorBGR(255,0,255),
    colorBGR(255,255,255),
    colorBGR(0,0,0)
  };

  for (int i = 0; i < 8; i++) {
    tft.fillScreen(colors[i]);
    delay(400);
  }
}

// 🌈 Gradient
void gradientTest() {
  for (int x = 0; x < tft.width(); x++) {
    uint16_t color = colorBGR(x * 3, 0, 255 - x * 3);
    tft.drawFastVLine(x, 0, tft.height(), color);
  }
}

// 📏 Lines
void lineTest() {
  tft.fillScreen(colorBGR(0,0,0));

  for (int x = 0; x < tft.width(); x += 5) {
    tft.drawLine(0, 0, x, tft.height(), colorBGR(255,0,0));
  }

  for (int y = 0; y < tft.height(); y += 5) {
    tft.drawLine(0, 0, tft.width(), y, colorBGR(0,0,255));
  }
}

// 🔷 Shapes
void shapeTest() {
  tft.fillScreen(colorBGR(0,0,0));

  tft.drawRect(5, 5, 40, 25, colorBGR(255,255,255));
  tft.fillRect(50, 5, 40, 25, colorBGR(0,255,0));

  tft.drawCircle(30, 55, 15, colorBGR(255,255,0));
  tft.fillCircle(90, 55, 15, colorBGR(255,0,0));
}

// 🔤 Text
void textTest() {
  tft.fillScreen(colorBGR(0,0,0));

  tft.setTextColor(colorBGR(255,255,255));
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.println("BUG LCD TEST");

  tft.setTextColor(colorBGR(0,255,0));
  tft.setTextSize(2);
  tft.setCursor(5, 20);
  tft.println("RP2040");

  tft.setTextColor(colorBGR(255,255,0));
  tft.setTextSize(1);
  tft.setCursor(5, 45);
  tft.println("DISPLAY OK");

  tft.setTextColor(colorBGR(0,255,255));
  tft.setCursor(5, 60);
  tft.println("ST7735 READY");
}