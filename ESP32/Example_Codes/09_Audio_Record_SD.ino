#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include "driver/i2s_std.h"

// ==================== LCD PINS ====================
#define TFT_DC    14
#define TFT_CS    4
#define TFT_RST   5
#define TFT_BL    38
#define TFT_SCLK  18
#define TFT_MOSI  17

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC,
  TFT_MOSI, TFT_SCLK,
  TFT_RST
);

// ==================== AUDIO CONFIG ====================
const uint32_t SAMPLE_RATE  = 16000;
const uint16_t SAMPLE_BITS  = 16;
const uint16_t CHANNELS     = 1;
const uint16_t RECORD_SECONDS = 5;

// ==================== SD PINS ====================
#define SD_CS    10
#define SD_MOSI  11
#define SD_CLK   12
#define SD_MISO  13

// ==================== MIC ====================
#define MIC_BCLK  7
#define MIC_WS    9
#define MIC_DATA  8

i2s_chan_handle_t rx_handle;

// ==================== WAV HEADER ====================
void writeWavHeader(File &file, uint32_t dataSize) {
  uint8_t h[44];

  uint32_t byteRate   = SAMPLE_RATE * CHANNELS * SAMPLE_BITS / 8;
  uint16_t blockAlign = CHANNELS * SAMPLE_BITS / 8;
  uint32_t chunkSize  = dataSize + 36;

  memcpy(h + 0,  "RIFF", 4);
  memcpy(h + 4,  &chunkSize, 4);
  memcpy(h + 8,  "WAVE", 4);
  memcpy(h + 12, "fmt ", 4);

  uint32_t subChunk1 = 16;
  uint16_t audioFmt  = 1;

  memcpy(h + 16, &subChunk1, 4);
  memcpy(h + 20, &audioFmt, 2);
  memcpy(h + 22, &CHANNELS, 2);
  memcpy(h + 24, &SAMPLE_RATE, 4);
  memcpy(h + 28, &byteRate, 4);
  memcpy(h + 32, &blockAlign, 2);
  memcpy(h + 34, &SAMPLE_BITS, 2);
  memcpy(h + 36, "data", 4);
  memcpy(h + 40, &dataSize, 4);

  file.seek(0);
  file.write(h, 44);
}

// ==================== MIC INIT ====================
void initMic() {
  i2s_chan_config_t chan_cfg = {
    .id = I2S_NUM_0,
    .role = I2S_ROLE_MASTER,
    .dma_desc_num = 8,
    .dma_frame_num = 256,
    .auto_clear = true
  };

  ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, NULL, &rx_handle));

  i2s_std_config_t std_cfg = {
    .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
    .slot_cfg = {
      .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
      .slot_bit_width = I2S_SLOT_BIT_WIDTH_16BIT,
      .slot_mode      = I2S_SLOT_MODE_MONO,
      .slot_mask      = I2S_STD_SLOT_RIGHT,
      .ws_width       = 16,
      .ws_pol         = true,
      .bit_shift      = false
    },
    .gpio_cfg = {
      .mclk = I2S_GPIO_UNUSED,
      .bclk = (gpio_num_t)MIC_BCLK,
      .ws   = (gpio_num_t)MIC_WS,
      .dout = I2S_GPIO_UNUSED,
      .din  = (gpio_num_t)MIC_DATA
    }
  };

  ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle, &std_cfg));
  ESP_ERROR_CHECK(i2s_channel_enable(rx_handle));

  Serial.println("Mic Ready");
}

// ==================== SIMPLE UI ====================
void showMsg(const char* msg) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.println(msg);
}

// ==================== RECORD ====================
void recordAudio() {

  showMsg("Recording...");

  File f = SD.open("/bug_record.wav", FILE_WRITE);
  if (!f) {
    showMsg("SD FAIL");
    return;
  }

  uint8_t blank[44] = {0};
  f.write(blank, 44);

  int16_t buffer[256];
  size_t bytesRead;
  uint32_t totalBytes = 0;

  unsigned long start = millis();

  while (millis() - start < RECORD_SECONDS * 1000) {

    ESP_ERROR_CHECK(
      i2s_channel_read(rx_handle, buffer, sizeof(buffer), &bytesRead, portMAX_DELAY)
    );

    int samples = bytesRead / 2;

    for (int i = 0; i < samples; i++) {
      int16_t sample = buffer[i];

      sample = sample * 2; // gain

      if (abs(sample) < 50) sample = 0;

      buffer[i] = sample;
    }

    f.write((uint8_t*)buffer, bytesRead);
    totalBytes += bytesRead;
  }

  writeWavHeader(f, totalBytes);
  f.close();

  showMsg("Saved!");
}

// ==================== SETUP ====================
void setup() {

  Serial.begin(115200);

  // LCD
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  tft.initR(INITR_MINI160x80);   // 🔥 KEY CHANGE
  tft.setRotation(1);
  tft.invertDisplay(true);

  showMsg("BUG READY");

  // SD
  SPIClass SPI_SD(HSPI);
  SPI_SD.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);

  if (!SD.begin(SD_CS, SPI_SD)) {
    showMsg("SD FAIL");
    while (1);
  }

  showMsg("SD OK");

  // MIC
  initMic();

  delay(1000);

  // RECORD
  recordAudio();
}

// ==================== LOOP ====================
void loop() {}