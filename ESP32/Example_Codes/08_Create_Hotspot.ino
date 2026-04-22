#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "esp_wifi.h"

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

// -------- AP CONFIG --------
const char* ap_ssid = "BUG_AP";
const char* ap_pass = "12345678";

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

// ================= CLIENT DISPLAY =================

int lastCount = -1;

void showClients() {

  wifi_sta_list_t stationList;
  esp_wifi_ap_get_sta_list(&stationList);

  int count = stationList.num;

  if (count != lastCount) {

    tft.fillScreen(C(0,0,0));

    centerText("Clients: " + String(count), 0, C(0,255,0), 1);

    for (int i = 0; i < count && i < 3; i++) {

      uint8_t *mac = stationList.sta[i].mac;

      char macStr[18];
      sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
              mac[0], mac[1], mac[2],
              mac[3], mac[4], mac[5]);

      tft.setCursor(0, 15 + i * 18);
      tft.setTextColor(C(255,255,255));
      tft.setTextSize(1);

      tft.print("MAC:");
      tft.println(macStr);
    }

    lastCount = count;
  }
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);

  tft.fillScreen(C(0,0,0));

  // Start AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_pass);

  IPAddress ip = WiFi.softAPIP();

  // 🔥 SHOW AP INFO
  tft.fillScreen(C(0,0,0));
  centerText("BUG HOTSPOT", 0, C(0,255,255), 1);
  centerText("SSID: " + String(ap_ssid), 15, C(255,255,255), 1);
  centerText("PASS: " + String(ap_pass), 30, C(255,255,255), 1);
  centerText(ip.toString(), 50, C(0,255,0), 1);

  delay(6000);

  tft.fillScreen(C(0,0,0));
}

// ================= LOOP =================

void loop() {
  showClients();
  delay(1000);
}