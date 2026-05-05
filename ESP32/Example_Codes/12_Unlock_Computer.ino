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

// ===== COLORS =====
uint16_t bg       = tft.color565(0, 0, 0);
uint16_t card     = tft.color565(30, 30, 30);
uint16_t accent   = tft.color565(0, 180, 255);
uint16_t success  = tft.color565(0, 255, 120);
uint16_t text     = tft.color565(255, 255, 255);
uint16_t dimText  = tft.color565(150, 150, 150);

// ===== CENTER TEXT =====
void centerText(String txt, int y, int size, uint16_t color) {
  int16_t x1, y1;
  uint16_t w, h;
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(txt, 0, y, &x1, &y1, &w, &h);
  int x = (tft.width() - w) / 2;
  tft.setCursor(x, y);
  tft.print(txt);
}

// ===== CARD =====
void drawCard(int y, String title, String subtitle) {
  tft.fillRoundRect(10, y, 140, 30, 6, card);
  tft.drawRoundRect(10, y, 140, 30, 6, accent);

  tft.setTextColor(text);
  tft.setTextSize(1);
  tft.setCursor(20, y + 8);
  tft.print(title);

  tft.setTextColor(dimText);
  tft.setCursor(20, y + 18);
  tft.print(subtitle);
}

// ===== HID START =====
void startHID() {
  USB.begin();
  Keyboard.begin();
  delay(1000); // PC detect delay
}

// ===== SAFE FOCUS FUNCTION =====
void focusLoginScreen() {

  // Wake screen (press Enter)
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  delay(300);

  // Type YOUR PASSWORD
  Keyboard.print("YOUR_PASSWORD");
  delay(1000);

  // Press ENTER
  Keyboard.press(KEY_RETURN);
  delay(1000);
  Keyboard.releaseAll();
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);
  tft.fillScreen(bg);

  // ===== SPLASH =====
  centerText("BUG", 10, 2, accent);
  centerText("System UI", 40, 1, text);
  delay(1500);

  // ===== INITIAL =====
  tft.fillScreen(bg);
  drawCard(10, "Mode", "Wake & Focus");
  drawCard(45, "Status", "Initializing");

  delay(1500);

  // ===== HID START =====
  startHID();

  // ===== EXECUTION =====
  drawCard(10, "Mode", "Wake & Focus");
  drawCard(45, "Status", "Executing");

  delay(500);

  focusLoginScreen();

  delay(800);

  // ===== SUCCESS =====
  drawCard(10, "Mode", "Wake & Focus");
  drawCard(45, "Status", "Screen Active");

  delay(1500);

  // ===== FINAL =====
  tft.fillScreen(bg);
  centerText("READY", 20, 2, success);
  centerText("Login Screen", 50, 1, text);
}

void loop() {}