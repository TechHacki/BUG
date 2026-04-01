#include <SPI.h>
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

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST);

// 🔥 BGR FIX
uint16_t colorBGR(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// 🎯 CENTER TEXT
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

// ================= SETUP =================
void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.invertDisplay(true);
  tft.fillScreen(colorBGR(0,0,0));

  // ===== SPLASH =====
  drawCenter("BUG", 35, colorBGR(0,255,255), 3);
  drawCenter("HID SYSTEM", 65, colorBGR(255,255,255), 1);
  delay(1500);

  tft.fillScreen(colorBGR(0,0,0));

  // ===== LOADING =====
  drawCenter("Preparing HID..", 35, colorBGR(255,255,255), 1);
  delay(1000);

  // ===== READY =====
  tft.fillScreen(colorBGR(0,0,0));
  drawCenter("READY", 30, colorBGR(0,255,0), 2);
  delay(1500);

  // ===== PAYLOAD =====
  tft.fillScreen(colorBGR(0,0,0));
  drawCenter("OPENING", 30, colorBGR(255,255,0), 2);
  drawCenter("NOTEPAD...", 60, colorBGR(255,255,255), 1);

  // ================= HID =================
  Keyboard.begin();

  delay(2000);  // 🔥 CRITICAL (PC detection time)

  // 🔥 Open Windows Search (BEST METHOD)
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);

  // Type NOTEPAD slowly
  Keyboard.print("notepad");
  delay(700);

  // Press ENTER
  Keyboard.press(KEY_RETURN);
  delay(200);
  Keyboard.releaseAll();

  delay(2000);  // wait for Notepad

  // ===== TYPE TEXT =====
  Keyboard.println("Hey I am BUG");
  Keyboard.write(KEY_RETURN);
  delay(100);
  Keyboard.println("------------------------");
  Keyboard.write(KEY_RETURN);
  delay(100);
  Keyboard.println("STM32 HID Demo");
  Keyboard.write(KEY_RETURN);
  delay(100);
  Keyboard.println("Automated Payload");

  Keyboard.end();

  // ===== DONE SCREEN =====
  tft.fillScreen(colorBGR(0,0,0));
  drawCenter("NOTEPAD", 35, colorBGR(0,255,0), 2);
  drawCenter("PAYLOAD SENT", 65, colorBGR(255,255,255), 1);
}

void loop() {}