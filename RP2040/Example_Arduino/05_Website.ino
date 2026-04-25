#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keyboard.h>

// ===== TFT PINS (RP2040 working setup) =====
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

// ===== COLORS =====
uint16_t bg      = 0x0000;
uint16_t card    = 0x294A;
uint16_t accent  = 0x07FF;
uint16_t success = 0x07E0;
uint16_t text    = 0xFFFF;
uint16_t dim     = 0x7BEF;

// ===== UI HELPERS =====
uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

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

void drawCard(int y, String title, String subtitle) {
  tft.fillRoundRect(10, y, 140, 30, 6, card);
  tft.drawRoundRect(10, y, 140, 30, 6, accent);

  tft.setTextSize(1);
  tft.setTextColor(text);
  tft.setCursor(20, y + 8);
  tft.print(title);

  tft.setTextColor(dim);
  tft.setCursor(20, y + 18);
  tft.print(subtitle);
}

void loadingBar(int p) {
  tft.drawRoundRect(20, 60, 120, 8, 4, dim);
  tft.fillRoundRect(20, 60, p, 8, 4, accent);
}

// ===== UI SCREENS =====
void splashScreen() {
  tft.fillScreen(bg);
  centerText("BUG", 10, 2, accent);
  centerText("Smart Launcher", 45, 1, text);
  delay(1500);
}

void loadingScreen() {
  tft.fillScreen(bg);
  centerText("Preparing...", 20, 1, text);

  for (int i = 0; i <= 120; i += 10) {
    loadingBar(i);
    delay(80);
  }
}

void mainScreen() {
  tft.fillScreen(bg);
  drawCard(10, "Browser", "Starting...");
  drawCard(45, "Target", "kickstarter.com");
}

// ===== HID STEPS =====
void openChrome() {

  drawCard(10, "Browser", "Opening...");

  Keyboard.begin();
  delay(3000);

  // Open Windows search
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();

  delay(800);

  // Type chrome
  Keyboard.print("chrome");
  delay(500);

  Keyboard.write(KEY_RETURN);

  delay(4000);

  drawCard(10, "Browser", "Opened");
}

void openWebsite() {

  drawCard(45, "Target", "Loading...");

  // Ctrl + L (address bar)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('l');
  delay(150);
  Keyboard.releaseAll();

  delay(300);

  Keyboard.print("https://www.kickstarter.com");
  delay(300);

  Keyboard.write(KEY_RETURN);

  delay(2500);

  drawCard(45, "Target", "Loaded");
}

// ===== SETUP =====
void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);

  splashScreen();
  loadingScreen();
  mainScreen();

  openChrome();
  openWebsite();

  // DONE SCREEN
  tft.fillScreen(bg);
  centerText("SUCCESS", 20, 2, success);
  centerText("Kickstarter Opened", 50, 1, text);

  Keyboard.end();
}

// ===== LOOP =====
void loop() {}