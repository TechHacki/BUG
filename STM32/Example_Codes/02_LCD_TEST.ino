#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// -------- TFT PINS --------
#define TFT_MOSI  PB15
#define TFT_SCLK  PB10
#define TFT_CS    PB12
#define TFT_DC    PB14
#define TFT_RST   PB13
#define TFT_BL    PB9

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// 🔥 BGR COLOR FIX
uint16_t colorBGR(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// ================= SETUP =================
void setup() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.invertDisplay(true);
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

// 🎨 Solid Colors Test
void colorTest() {
  uint16_t colors[] = {
    colorBGR(255,0,0),   // RED
    colorBGR(0,255,0),   // GREEN
    colorBGR(0,0,255),   // BLUE
    colorBGR(255,255,0), // YELLOW
    colorBGR(0,255,255), // CYAN
    colorBGR(255,0,255), // MAGENTA
    colorBGR(255,255,255),
    colorBGR(0,0,0)
  };

  for (int i = 0; i < 8; i++) {
    tft.fillScreen(colors[i]);
    delay(500);
  }
}

// 🌈 Gradient
void gradientTest() {
  for (int x = 0; x < tft.width(); x++) {
    uint16_t color = colorBGR(x * 2, 0, 255 - x * 2);
    tft.drawFastVLine(x, 0, tft.height(), color);
  }
}

// 📏 Lines
void lineTest() {
  tft.fillScreen(colorBGR(0,0,0));

  for (int x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height(), colorBGR(255,0,0));
  }

  for (int y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width(), y, colorBGR(0,0,255));
  }
}

// 🔷 Shapes
void shapeTest() {
  tft.fillScreen(colorBGR(0,0,0));

  tft.drawRect(10, 10, 50, 30, colorBGR(255,255,255));
  tft.fillRect(70, 10, 50, 30, colorBGR(0,255,0));
  tft.drawCircle(40, 70, 20, colorBGR(255,255,0));
  tft.fillCircle(100, 70, 20, colorBGR(255,0,0));
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
  tft.setCursor(5, 25);
  tft.println("STM32");

  tft.setTextColor(colorBGR(255,255,0));
  tft.setTextSize(2);
  tft.setCursor(5, 50);
  tft.println("DISPLAY OK");

  tft.setTextColor(colorBGR(0,255,255));
  tft.setTextSize(1);
  tft.setCursor(5, 75);
  tft.println("Colors + Shapes + Text");
}