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

// ===== SELECT OS HERE =====
#define TARGET_OS 0   // 0=Windows | 1=macOS | 2=Linux

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

// ===== GET OS NAME =====
String getOSName() {
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

// ===== LOCK FUNCTION =====
void lockComputer() {

  #if TARGET_OS == 0
    // Windows: Win + L
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(200);
    Keyboard.releaseAll();

  #elif TARGET_OS == 1
    // macOS: Ctrl + Cmd + Q
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('q');
    delay(200);
    Keyboard.releaseAll();

  #elif TARGET_OS == 2
    // Linux: Ctrl + Alt + L
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('l');
    delay(200);
    Keyboard.releaseAll();

  #endif
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

  drawCard(10, "Mode", "Computer Lock");
  drawCard(45, "OS", getOSName());

  delay(2000);

  // ===== HID START =====
  Keyboard.begin();
  delay(3000); // PC ready

  drawCard(10, "Mode", "Locking...");
  drawCard(45, "OS", getOSName());

  // ===== EXECUTE LOCK =====
  lockComputer();

  delay(1000);

  drawCard(10, "Mode", "Locked");
  drawCard(45, "Status", "Success");

  Keyboard.end();

  // ===== FINAL =====
  tft.fillScreen(bg);
  centerText("LOCKED", 25, 2, success);
  centerText(getOSName(), 55, 1, text);
}

void loop() {}