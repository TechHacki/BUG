#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// -------- LCD (Software SPI) --------
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

File bmpFile;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // LCD INIT
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.invertDisplay(true);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.println("LCD OK");

  // 🔥 SPI1 for SD
  SPI.setMOSI(PB5);
  SPI.setMISO(PB4);
  SPI.setSCLK(PB3);
  SPI.begin();

  if (!SD.begin(SD_CS)) {
    tft.setCursor(10, 60);
    tft.println("SD FAIL");
    while (1);
  } else {
    tft.setCursor(10, 60);
    tft.println("SD OK");
  }

  delay(1500);
  tft.fillScreen(ST77XX_BLACK);

  // 👉 SHOW BMP
  drawBMP("/BUG.bmp", 0, 25);
}

void loop() {}


// ================= BMP FUNCTION =================

void drawBMP(const char *filename, int x, int y) {

  bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.println("File not found");
    return;
  }

  // Check BMP signature
  if (read16(bmpFile) != 0x4D42) {
    Serial.println("Not BMP");
    bmpFile.close();
    return;
  }

  read32(bmpFile); // file size
  read32(bmpFile); // reserved
  uint32_t offset = read32(bmpFile);

  read32(bmpFile); // header size
  int width  = read32(bmpFile);
  int height = read32(bmpFile);

  if (read16(bmpFile) != 1) {
    bmpFile.close();
    return;
  }

  uint16_t depth = read16(bmpFile);
  if (depth != 24) {
    Serial.println("Only 24-bit BMP");
    bmpFile.close();
    return;
  }

  if (read32(bmpFile) != 0) {
    bmpFile.close();
    return;
  }

  uint32_t rowSize = (width * 3 + 3) & ~3;

  bool flip = true;
  if (height < 0) {
    height = -height;
    flip = false;
  }

  tft.startWrite();

  for (int row = 0; row < height; row++) {

    uint32_t pos = flip
      ? offset + (height - 1 - row) * rowSize
      : offset + row * rowSize;

    bmpFile.seek(pos);

    for (int col = 0; col < width; col++) {

      uint8_t b = bmpFile.read();
      uint8_t g = bmpFile.read();
      uint8_t r = bmpFile.read();

      uint16_t color = tft.color565(b, g, r);

      tft.drawPixel(x + col, y + row, color);
    }
  }

  tft.endWrite();
  bmpFile.close();
}


// ================= HELPERS =================

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
}