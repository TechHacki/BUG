#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keyboard.h>

// -------- TFT --------
#define TFT_MOSI PB15
#define TFT_SCLK PB10
#define TFT_CS   PB12
#define TFT_DC   PB14
#define TFT_RST  PB13
#define TFT_BL   PB9

// -------- SD (WORKING CONFIG) --------
#define SD_CS PB6

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST);

// ================= UI =================

uint16_t colorBGR(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

void drawCenter(String text, int y, uint16_t color, int size) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);

  int x = (tft.width() - w) / 2;
  tft.setCursor(x, y);
  tft.println(text);
}

// ================= DUCKY ENGINE =================

void executeLine(String line) {

  line.trim();
  if (line.length() == 0) return;

  if (line.startsWith("DELAY ")) {
    delay(line.substring(6).toInt());
  }

  else if (line.startsWith("STRING ")) {
    Keyboard.print(line.substring(7));
  }

  else if (line == "ENTER") {
    Keyboard.write(KEY_RETURN);
  }

  else if (line == "GUI") {
    Keyboard.press(KEY_LEFT_GUI);
    delay(100);
    Keyboard.releaseAll();
  }

  else if (line == "CMD SPACE") {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
    delay(100);
    Keyboard.releaseAll();
  }

  else if (line == "CTRL ALT T") {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('t');
    delay(100);
    Keyboard.releaseAll();
  }
}

// ================= RUN SCRIPT =================

void runPayload(const char* filename) {

  File file = SD.open(filename);

  if (!file) {
    drawCenter("NO FILE", 70, colorBGR(255,0,0), 1);
    return;
  }

  Keyboard.begin();
  delay(2000); // USB detection

  String line = "";

  while (file.available()) {
    char c = file.read();

    if (c == '\n') {
      executeLine(line);
      line = "";
    } else if (c != '\r') {
      line += c;
    }
  }

  if (line.length() > 0) executeLine(line);

  file.close();
  Keyboard.end();
}

// ================= SETUP =================

void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // TFT INIT
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.invertDisplay(true);
  tft.fillScreen(ST77XX_BLACK);

  drawCenter("BUG", 30, colorBGR(0,255,255), 2);
  drawCenter("HID SYSTEM", 60, colorBGR(255,255,255), 1);
  delay(1500);

  // ================= SD INIT =================

  drawCenter("INIT SD...", 90, colorBGR(255,255,255), 1);

  // SD Card Config
  SPI.setMOSI(PB5);
  SPI.setMISO(PB4);
  SPI.setSCLK(PB3);
  SPI.begin();

  if (!SD.begin(SD_CS)) {
    drawCenter("SD FAIL", 110, colorBGR(255,0,0), 1);
    while (1);
  }

  drawCenter("SD OK", 110, colorBGR(0,255,0), 1);
  delay(1000);

  // ================= RUN PAYLOAD =================

  tft.fillScreen(ST77XX_BLACK);
  drawCenter("RUNNING...", 60, colorBGR(255,255,0), 2);

  runPayload("/payload.txt");

  // ================= DONE =================

  tft.fillScreen(ST77XX_BLACK);
  drawCenter("DONE", 70, colorBGR(0,255,0), 2);
}

void loop() {}