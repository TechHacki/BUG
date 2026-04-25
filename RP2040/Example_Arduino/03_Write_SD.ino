#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// -------- TFT (Software SPI - SAME AS YOUR WORKING SETUP) --------
#define TFT_DC   8
#define TFT_CS   9
#define TFT_RST  12
#define TFT_BL   13

#define TFT_MOSI 11
#define TFT_SCLK 10

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// -------- SD (Hardware SPI) --------
#define SD_CS 17

File myFile;

// 🔥 COLOR FIX (BGR)
uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// ================= UI FUNCTIONS =================

// Center text
void drawCenterText(String text, int y, uint16_t color, int size) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.setTextSize(size);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (tft.width() - w) / 2;

  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.println(text);
}

// Card UI
void drawCard(int x, int y, int w, int h, uint16_t border) {
  tft.drawRoundRect(x, y, w, h, 6, border);
}

// Loading animation
void loadingAnim(String baseText, int y) {
  for (int i = 0; i < 3; i++) {
    tft.fillRect(0, y, 160, 20, C(0,0,0));

    drawCenterText(baseText + ".", y, C(255,255,255), 1);
    delay(250);

    drawCenterText(baseText + "..", y, C(255,255,255), 1);
    delay(250);

    drawCenterText(baseText + "...", y, C(255,255,255), 1);
    delay(250);
  }
}

// ================= SETUP =================

void setup() {
  Serial.begin(115200);

  // Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // ===== TFT INIT =====
  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);
  tft.fillScreen(C(0,0,0));

  // ===== SPLASH =====
  drawCenterText("BUG", 10, C(0,255,255), 2);
  drawCenterText("SYSTEM", 30, C(255,255,255), 1);
  delay(1200);

  tft.fillScreen(C(0,0,0));

  // ===== INIT ANIMATION =====
  loadingAnim("Initializing SD", 35);

  // ===== SD INIT =====
  SPI.begin();  // hardware SPI

  tft.fillScreen(C(0,0,0));
  drawCard(10, 20, 140, 40, C(100,100,100));

  if (!SD.begin(SD_CS)) {
    drawCenterText("SD FAILED", 30, C(255,0,0), 1);
    while (1);
  }

  drawCenterText("SD READY", 30, C(0,255,0), 1);
  delay(1000);

  // ===== WRITE FILE UI =====
  tft.fillScreen(C(0,0,0));
  drawCard(10, 20, 140, 40, C(0,255,255));

  drawCenterText("WRITING...", 30, C(255,255,255), 1);

  SD.remove("/BUG.txt");
  myFile = SD.open("/BUG.txt", FILE_WRITE);

  delay(500);

  if (myFile) {
    myFile.println("Hey I am BUG (RP2040)");
    myFile.close();

    tft.fillScreen(C(0,0,0));
    drawCenterText("SUCCESS", 20, C(0,255,0), 2);
    drawCenterText("FILE CREATED", 45, C(255,255,255), 1);

  } else {
    tft.fillScreen(C(0,0,0));
    drawCenterText("ERROR", 20, C(255,0,0), 2);
    drawCenterText("WRITE FAILED", 45, C(255,255,255), 1);
  }
}

// ================= LOOP =================
void loop() {}