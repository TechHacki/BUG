#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keyboard.h>
#include <Mouse.h>

// -------- TFT --------
#define TFT_MOSI PB15
#define TFT_SCLK PB10
#define TFT_CS   PB12
#define TFT_DC   PB14
#define TFT_RST  PB13
#define TFT_BL   PB9

// ===== SELECT OS HERE =====
#define TARGET_OS 0   // 0=Windows | 1=macOS | 2=Linux

// ===== AVOID CONFLICT NAMES =====
int regionX1 = 660;
int regionY1 = 340;
int regionX2 = 1260;
int regionY2 = 740;

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// ===== COLORS =====
uint16_t bg     = tft.color565(0, 0, 0);
uint16_t card   = tft.color565(25, 25, 25);
uint16_t accent = tft.color565(0, 180, 255);
uint16_t ok     = tft.color565(0, 255, 120);
uint16_t warn   = tft.color565(255, 180, 0);
uint16_t text   = tft.color565(255, 255, 255);
uint16_t dim    = tft.color565(150, 150, 150);

// ===== UI =====
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

void drawCard(int y, String title, String subtitle, uint16_t c) {
  tft.fillRoundRect(10, y, 140, 30, 6, card);
  tft.drawRoundRect(10, y, 140, 30, 6, c);

  tft.setTextColor(text);
  tft.setTextSize(1);
  tft.setCursor(20, y + 8);
  tft.print(title);

  tft.setTextColor(dim);
  tft.setCursor(20, y + 18);
  tft.print(subtitle);
}

// ===== OS NAME =====
String getOS() {
#if TARGET_OS == 0
  return "Windows";
#elif TARGET_OS == 1
  return "macOS";
#elif TARGET_OS == 2
  return "Linux";
#else
  return "Unknown";
#endif
}

// ===== SAFE MOUSE MOVE =====
void moveMouseSmooth(int dx, int dy) {
  int steps = 10;
  for (int i = 0; i < steps; i++) {
    Mouse.move(dx / steps, dy / steps);
    delay(20);
  }
}

// ===== SCREENSHOT FUNCTION =====
void takeScreenshot() {

  Keyboard.begin();
  delay(500);

#if TARGET_OS == 0
  // Windows: Win + PrintScreen (auto-save)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('s');
  delay(200);
  Keyboard.releaseAll();

#elif TARGET_OS == 1
  // macOS: Cmd + Shift + 3
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('3');
  delay(200);
  Keyboard.releaseAll();

#elif TARGET_OS == 2
  // Linux: PrintScreen
  Keyboard.press(0x46);
  delay(200);
  Keyboard.releaseAll();

#endif

  delay(1500);

  // Move cursor (approx positioning)
  Mouse.move(-50, -50);
  delay(200);

  // Drag start → end
  Mouse.press(MOUSE_LEFT);
  delay(200);

  int dx = regionX2 - regionX1;
  int dy = regionY2 - regionY1;

  moveMouseSmooth(dx / 5, dy / 5);

  Mouse.release(MOUSE_LEFT);

  delay(500);

  Keyboard.end();
  Mouse.end();
}

// ================= SETUP =================
void setup() {

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.invertDisplay(true);
  tft.fillScreen(bg);

  // ===== BOOT UI =====
  centerText("BUG UI", 10, 2, accent);
  centerText("Screenshot System", 40, 1, text);
  delay(1500);

  // ===== MAIN UI =====
  tft.fillScreen(bg);

  drawCard(10, "Mode", "Screenshot Capture", accent);
  drawCard(45, "OS", getOS(), warn);

  delay(2000);

  // ===== EXECUTION =====
  drawCard(10, "Mode", "Capturing...", warn);
  drawCard(45, "Status", "Processing", dim);

  delay(800);

  takeScreenshot();

  // ===== SUCCESS =====
  drawCard(10, "Mode", "Completed", ok);
  drawCard(45, "Status", "Saved", ok);

  delay(1500);

  // ===== FINAL SCREEN =====
  tft.fillScreen(bg);
  centerText("DONE", 20, 2, ok);
  centerText(getOS(), 50, 1, text);
}

void loop() {}