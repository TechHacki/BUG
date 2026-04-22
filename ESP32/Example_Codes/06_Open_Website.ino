#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

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

// -------- HID --------
USBHIDKeyboard Keyboard;

// ================= UI =================

uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

void drawCard(int x, int y, int w, int h, uint16_t border) {
  tft.drawRoundRect(x, y, w, h, 6, border);
}

void centerText(String text, int y, uint16_t color, int size) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.setTextSize(size);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (tft.width() - w) / 2;
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.println(text);
}

void showScreen(String title, String msg, uint16_t color) {
  tft.fillScreen(C(0,0,0));

  drawCard(5, 5, 150, 30, color);
  drawCard(5, 40, 150, 30, C(80,80,80));

  centerText(title, 12, color, 1);
  centerText(msg, 50, C(255,255,255), 1);
}

// ================= HID =================

void startHID() {
  USB.begin();
  Keyboard.begin();
  delay(800); // allow PC detect keyboard
}

void openWebsite() {

  // STEP 1: Open Run
  showScreen("STEP 1", "Opening Run", C(0,255,255));

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(700);

  // STEP 2: Type URL
  showScreen("STEP 2", "Launching Browser", C(255,255,0));

  Keyboard.print("https://www.google.com");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(1500);

  // DONE
  showScreen("DONE", "Website Opened", C(0,255,0));
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  // TFT INIT
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);

  tft.fillScreen(C(0,0,0));

  // Splash
  centerText("BUG WEB", 10, C(0,255,255), 2);
  centerText("AUTO MODE", 35, C(255,255,255), 1);

  // 🔥 Safety delay
  for (int i = 5; i > 0; i--) {
    centerText("Starting in " + String(i), 55, C(255,255,0), 1);
    delay(1000);
  }

  showScreen("STATUS", "Opening Site", C(0,255,0));

  startHID();
  openWebsite();
}

// ================= LOOP =================

void loop() {
  // run only once
}