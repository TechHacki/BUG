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
  TFT_RST
);

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

// ================= SETUP =================
void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.invertDisplay(true);
  tft.fillScreen(bg);

  // ===== SPLASH =====
  centerText("BUG", 10, 3, accent);
  centerText("System UI", 45, 1, text);
  delay(1500);

  // ===== MAIN UI =====
  tft.fillScreen(bg);

  drawCard(10, "Recycle Bin", "Opening...");
  drawCard(45, "Status", "Preparing");

  delay(2000);

  // ================= HID =================
  Keyboard.begin();
  delay(4000); // PC ready

  // Open RUN
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(200);
  Keyboard.releaseAll();

  delay(1000);

  // Open Recycle Bin
  Keyboard.print("shell:RecycleBinFolder");
  delay(400);

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(2000);

  // Update UI
  drawCard(10, "Recycle Bin", "Opened..!");
  drawCard(45, "Status", "Awaiting action");

  Keyboard.end();

  // ===== DONE =====
  tft.fillScreen(bg);
  centerText("READY", 25, 2, success);
  centerText("Recycle Bin Opened", 55, 1, text);
}

void loop() {}