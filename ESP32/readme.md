# 🐞 BUG – ESP32-S3

## 🚀 Overview

BUG is a compact and powerful hardware platform designed for developers, makers, and hardware enthusiasts.  
This repository contains the **ESP32-S3 Arduino firmware** for BUG, enabling advanced applications with **WiFi, BLE, and native USB HID support**.

With integrated display, SD card support, and wireless connectivity, BUG becomes a **portable smart automation and development platform**.

---

## ✨ Features

### ⚡ High Performance (ESP32-S3)

* Dual-core processor
* Fast execution and low latency
* Optimized for wireless 

---

### 🔌 Native USB HID

* Works as **Keyboard / Mouse**
* No external chip required
* Perfect for automation and scripting

---

### 📺 TFT Display (0.96" TFT)

* ST7735-based LCD support  
* 160x80 resolution  
* Smooth UI rendering  
* Text, graphics, and animation support  

| Function | Pin |
|--------|-----|
| MOSI   | GPIO 17 |
| SCLK   | GPIO 18 |
| CS     | GPIO 4 |
| DC     | GPIO 14  |
| RST    | GPIO 5  |
| BL     | GPIO 38  |

---

### 💾 SD Card Support

* Read/write files from SD card  
* Store payloads, logs, and images  
* Used for dynamic content and scripting  

| Function | Pin |
|--------|-----|
| CS     | GPIO 10  |
| MOSI   | GPIO 11 |
| MISO   | GPIO 13 |
| SCLK   | GPIO 12 |

---

### 📡 WiFi + BLE

* Built-in wireless connectivity  
* WiFi scanning and automation  
* BLE device interaction  

---

### 🌈 RGB LED

* WS2812 RGB LED support  
* Status indication and animations  

| Function | Pin |
|--------|------|
| Data   | GPIO 45 |

---


### 🌈 MIC

* WS2812 RGB LED support  
* Status indication and animations  

| Function | Pin |
|--------|------|
| SCK    | GPIO 7 |
| DATA   | GPIO 8 |
| WS     | GPIO 9 |

---

### 🧩 Modular Firmware Design

* Clean and reusable code structure  
* Separate modules for display, SD, HID, and wireless  
* Easy to expand and customize  

---

### 🛠 Developer Friendly

* Arduino + ESP-IDF compatible  
* Easy to modify and extend  
* Large ecosystem support  

---

# 🛠 Getting Started with Arduino

### Step 1. Install ESP32 Board Support

1. Open **Arduino IDE**  
2. Go to:  
   `File → Preferences`  

3. In **Additional Board Manager URLs**, add:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

4. Click **OK**

---

### Step 2. Install ESP32 Core

1. Go to:  
   `Tools → Board → Boards Manager`  

2. Search for: ESP32 by Espressif Systems and install It.

---

### Step 2. Install the Libraries

1. Go to -> Library Manager and install the following libraries
   - Adafruit_ST7735
   - Adafruit_GFX
   - Adafruit_NeoPixel
  
---

### Step 3 - Check the Tool Info

<img width="1000" height="800" alt="image" src="https://github.com/user-attachments/assets/8a71fb43-d10a-41aa-8224-1345b03317a7" />



