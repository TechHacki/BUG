#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
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

// -------- WIFI AP --------
const char* ssid = "BUG_UI";
const char* password = "12345678";

WebServer server(80);

// ================= LCD =================

uint16_t C(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(b, g, r);
}

void showText(String msg) {
  tft.fillScreen(C(0,0,0));
  tft.setCursor(5, 30);
  tft.setTextColor(C(255,255,255));
  tft.setTextSize(1);
  tft.println(msg);
}

// ================= WEB PAGE =================

String webpage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: Arial; text-align: center; background:#111; color:white; }
button {
  padding: 15px;
  margin: 10px;
  width: 80%;
  font-size: 18px;
  border-radius: 10px;
}
input {
  padding: 10px;
  width: 80%;
  font-size: 16px;
}
</style>
</head>
<body>

<h2>BUG CONTROL</h2>

<button onclick="sendData('color')">Change Color</button>
<button onclick="sendData('btn2')">Button 2</button>
<button onclick="sendData('btn3')">Button 3</button>
<button onclick="sendData('btn4')">Button 4</button>

<br><br>

<input id="msg" placeholder="Enter text">
<br><br>
<button onclick="sendText()">Send Text</button>

<script>
function sendData(val){
  fetch('/cmd?data=' + val);
}

function sendText(){
  let txt = document.getElementById('msg').value;
  fetch('/text?msg=' + txt);
}
</script>

</body>
</html>
)rawliteral";

// ================= HANDLERS =================

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleCmd() {
  String data = server.arg("data");

  if (data == "color") {
    tft.fillScreen(random(0xFFFF));
  }
  else {
    showText("Pressed: " + data);
  }

  server.send(200, "text/plain", "OK");
}

void handleText() {
  String msg = server.arg("msg");
  showText(msg);
  server.send(200, "text/plain", "Text Received");
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  // LCD INIT
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.invertDisplay(true);

  tft.fillScreen(C(0,0,0));
  showText("Starting AP...");

  // WIFI AP
  WiFi.softAP(ssid, password);

  Serial.println(WiFi.softAPIP());

  showText("Connect WiFi:\nBUG_UI\n192.168.4.1");

  // ROUTES
  server.on("/", handleRoot);
  server.on("/cmd", handleCmd);
  server.on("/text", handleText);

  server.begin();
}

// ================= LOOP =================

void loop() {
  server.handleClient();
}