#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

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

// -------- WIFI --------
const char* ssid     = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// ================= UI =================

uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
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

void showScreen(String title, String msg) {
  tft.fillScreen(C(0,0,0));

  centerText(title, 10, C(0,255,255), 1);
  centerText(msg, 40, C(255,255,255), 1);
}

// ================= WIFI =================

void scanNetworks() {

  showScreen("WiFi", "Scanning...");

  int n = WiFi.scanNetworks();

  tft.fillScreen(C(0,0,0));

  if (n == 0) {
    centerText("No Networks", 30, C(255,0,0), 1);
    delay(2000);
    return;
  }

  for (int i = 0; i < n && i < 5; i++) {
    tft.setCursor(0, i * 12);
    tft.setTextColor(C(0,255,0));
    tft.setTextSize(1);

    String name = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);

    tft.print(name);
    tft.print(" (");
    tft.print(rssi);
    tft.println(")");
  }

  delay(3000);
}

void connectWiFi() {

  showScreen("WiFi", "Connecting...");

  WiFi.begin(ssid, password);

  int timeout = 0;

  while (WiFi.status() != WL_CONNECTED && timeout < 20) {
    delay(500);
    timeout++;
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {

    showScreen("Connected", WiFi.localIP().toString());

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());

  } else {

    showScreen("Failed", "Retry...");
    Serial.println("\nConnection Failed");

  }
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

  centerText("BUG WiFi", 10, C(0,255,255), 2);
  delay(1000);

  WiFi.mode(WIFI_STA);

  // Scan
  scanNetworks();

  // Connect
  connectWiFi();
}

// ================= LOOP =================

void loop() {}