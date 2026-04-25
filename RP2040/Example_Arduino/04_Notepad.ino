#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keyboard.h>

// ===== TFT PINS =====
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

// ================= UI HELPERS =================

uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

// Card UI (ESP32 style)
void drawCard(int x, int y, int w, int h, uint16_t border) {
  tft.drawRoundRect(x, y, w, h, 6, border);
}

// Center text
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

// Full screen UI block
void showScreen(String title, String msg, uint16_t color) {
  tft.fillScreen(C(0,0,0));

  drawCard(5, 5, 150, 30, color);
  drawCard(5, 40, 150, 30, C(80,80,80));

  centerText(title, 12, color, 1);
  centerText(msg, 50, C(255,255,255), 1);
}

// ================= HID =================

void startHID() {
  Keyboard.begin();
  delay(1000); // allow PC detection
}

void runPayload() {

  // STEP 1
  showScreen("STEP 1", "Opening Run", C(0,255,255));

  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(800);

  // STEP 2
  showScreen("STEP 2", "Opening Notepad", C(255,255,0));

  Keyboard.print("notepad");
  Keyboard.write(KEY_RETURN);

  delay(2000);

  // STEP 3
  showScreen("STEP 3", "Typing Message", C(0,255,0));

  Keyboard.print("I am Bug");

  delay(500);

  // DONE
  showScreen("DONE", "Completed", C(0,255,0));
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

  // Splash UI (ESP32 style)
  centerText("BUG HID", 10, C(0,255,255), 2);
  centerText("AUTO MODE", 35, C(255,255,255), 1);

  // countdown
  for (int i = 3; i > 0; i--) {
    centerText("Starting in " + String(i), 55, C(255,255,0), 1);
    delay(1000);
  }

  // Start
  showScreen("STATUS", "Running Payload", C(0,255,0));

  startHID();
  runPayload();
}

// ================= LOOP =================
void loop() {}