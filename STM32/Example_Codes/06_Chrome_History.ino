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

// ===== COLORS (BGR FIXED) =====
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

// ===== CARD UI =====
void drawCard(int y, String title, String subtitle) {
  tft.fillRoundRect(10, y, 140, 30, 6, card);
  tft.drawRoundRect(10, y, 140, 30, 6, accent);

  tft.setTextSize(1);
  tft.setTextColor(text);
  tft.setCursor(20, y + 8);
  tft.print(title);

  tft.setTextColor(dimText);
  tft.setCursor(20, y + 18);
  tft.print(subtitle);
}

// ===== LOADING BAR =====
void loadingBar(int progress) {
  tft.drawRoundRect(20, 60, 120, 8, 4, dimText);
  tft.fillRoundRect(20, 60, progress, 8, 4, accent);
}

// ================= SETUP =================
void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.invertDisplay(true);
  tft.fillScreen(bg);

  // ===== SPLASH =====
  centerText("BUG", 30, 3, accent);
  centerText("Smart HID Engine", 65, 1, text);
  delay(1500);

  // ===== LOADING SCREEN =====
  tft.fillScreen(bg);
  centerText("Initializing...", 30, 1, text);

  for (int i = 0; i <= 120; i += 10) {
    loadingBar(i);
    delay(100);
  }

  delay(500);

  // ===== MAIN CARD =====
  tft.fillScreen(bg);

  centerText("System Ready", 5, 1, success);

  drawCard(30, "Chrome Launcher", "Opening browser...");
  drawCard(65, "Navigation", "Loading history page");

  delay(2000);

  // ================= HID =================

  Keyboard.begin();
  delay(4000); // PC ready

  // Open Search
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();

  delay(800);

  // Open Chrome
  Keyboard.print("chrome");
  delay(600);

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(4000);

  // Update UI
  drawCard(30, "Chrome Launcher", "Opened..");

  // Focus address bar
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('l');
  delay(200);
  Keyboard.releaseAll();

  delay(300);

  // Go to history
  Keyboard.print("chrome://history/");
  delay(500);

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(1500);

  // Update UI
  drawCard(65, "Navigation", "History Loaded..");

  Keyboard.end();

  // ===== DONE SCREEN =====
  tft.fillScreen(bg);

  centerText("SUCCESS", 40, 2, success);
  centerText("Chrome History Opened", 70, 1, text);
}

void loop() {}