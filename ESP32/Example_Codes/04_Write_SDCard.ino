#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// -------- TFT --------
#define TFT_MOSI  17
#define TFT_SCLK  18
#define TFT_CS    4
#define TFT_DC    14
#define TFT_RST   5
#define TFT_BL    38

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// -------- SD --------
#define SD_CS    10
#define SD_MOSI  11
#define SD_MISO  13
#define SD_SCLK  12

SPIClass SPI_SD(HSPI);
File myFile;

// 🔥 COLOR FIX (BGR)
uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// ================= UI =================

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

void drawCard(int x, int y, int w, int h, uint16_t border) {
  tft.drawRoundRect(x, y, w, h, 6, border);
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

  // 🔥 IMPORTANT COLOR FIX
  tft.invertDisplay(true);

  tft.fillScreen(C(0,0,0));

  // ===== SPLASH =====
  drawCenterText("BUG", 10, C(0,255,255), 2);
  drawCenterText("SYSTEM", 30, C(255,255,255), 1);
  delay(1200);

  tft.fillScreen(C(0,0,0));

  // ===== INIT ANIMATION =====
  for (int i = 0; i < 3; i++) {
    tft.fillRect(0, 30, 160, 20, C(0,0,0));

    drawCenterText("Initializing SD.", 35, C(255,255,255), 1);
    delay(250);

    drawCenterText("Initializing SD..", 35, C(255,255,255), 1);
    delay(250);

    drawCenterText("Initializing SD...", 35, C(255,255,255), 1);
    delay(250);
  }

  // ===== SD INIT =====
  SPI_SD.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);

  tft.fillScreen(C(0,0,0));
  drawCard(10, 20, 140, 40, C(100,100,100));

  if (!SD.begin(SD_CS, SPI_SD)) {
    drawCenterText("SD FAILED", 30, C(255,0,0), 1);
    while (1);
  }

  drawCenterText("SD READY", 30, C(0,255,0), 1);
  delay(1000);

  // ===== WRITE FILE =====
  tft.fillScreen(C(0,0,0));
  drawCard(10, 20, 140, 40, C(0,255,255));

  drawCenterText("WRITING...", 30, C(255,255,255), 1);

  SD.remove("/BUG.txt");
  myFile = SD.open("/BUG.txt", FILE_WRITE);

  delay(500);

  if (myFile) {
    myFile.println("Hey I am BUG");
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