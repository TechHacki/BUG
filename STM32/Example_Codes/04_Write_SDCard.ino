#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// -------- TFT --------
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

// -------- SD --------
#define SD_CS PB6

File myFile;

// 🔥 BGR FIX
uint16_t colorBGR(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// ================= UI HELPERS =================

void drawCenterText(String text, int y, uint16_t color, int size) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);

  int x = (tft.width() - w) / 2;
  tft.setCursor(x, y);
  tft.println(text);
}

void drawCard(int x, int y, int w, int h, uint16_t border) {
  tft.drawRoundRect(x, y, w, h, 8, border);
}

// ================= SETUP =================

void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.invertDisplay(true);
  tft.fillScreen(colorBGR(0,0,0));

  // ===== SPLASH =====
  drawCenterText("BUG", 30, colorBGR(0,255,255), 3);
  drawCenterText("SYSTEM", 70, colorBGR(255,255,255), 1);
  delay(1500);

  tft.fillScreen(colorBGR(0,0,0));

  // ===== INIT ANIMATION =====
  for (int i = 0; i < 3; i++) {
    tft.fillRect(0, 30, 160, 30, colorBGR(0,0,0));
    drawCenterText("Initializing SD.", 40, colorBGR(255,255,255), 1);
    delay(300);
    drawCenterText("Initializing SD..", 40, colorBGR(255,255,255), 1);
    delay(300);
    drawCenterText("Initializing SD...", 40, colorBGR(255,255,255), 1);
    delay(300);
  }

  // ===== SD INIT =====
  SPI.setMOSI(PB5);
  SPI.setMISO(PB4);
  SPI.setSCLK(PB3);
  SPI.begin();

  tft.fillScreen(colorBGR(0,0,0));

  drawCard(10, 30, 140, 60, colorBGR(100,100,100));

  if (!SD.begin(SD_CS)) {

    drawCenterText("SD FAILED", 40, colorBGR(255,0,0), 2);

    while (1);
  }

  drawCenterText("SD READY", 50, colorBGR(0,255,0), 2);

  delay(1000);

  // ===== WRITING SCREEN =====
  tft.fillScreen(colorBGR(0,0,0));
  drawCard(10, 30, 140, 60, colorBGR(0,255,255));

  drawCenterText("WRITING...", 40, colorBGR(255,255,255), 2);

  // File write
  SD.remove("BUG.txt");
  myFile = SD.open("BUG.txt", FILE_WRITE);

  delay(800);

  if (myFile) {
    myFile.println("Hey I am BUG");
    myFile.close();

    // SUCCESS SCREEN
    tft.fillScreen(colorBGR(0,0,0));

    drawCenterText("SUCCESS", 30, colorBGR(0,255,0), 2);
    drawCenterText("FILE CREATED", 70, colorBGR(255,255,255), 1);

  } else {

    tft.fillScreen(colorBGR(0,0,0));

    drawCenterText("ERROR", 30, colorBGR(255,0,0), 2);
    drawCenterText("WRITE FAILED", 70, colorBGR(255,255,255), 1);
  }
}

void loop() {}