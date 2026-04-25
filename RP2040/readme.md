
# 🐞 BUG – RP2040

## 🚀 Overview

BUG is a compact and powerful hardware platform designed for developers, makers, and hardware enthusiasts.  
This repository contains the **RP2040 firmware** for BUG, enabling advanced applications with **Circuit Python and Arduino**.

With integrated display, SD card support, and wireless connectivity, BUG becomes a **portable smart automation and development platform**.

---

## ✨ Features

### ⚡ High Performance (RP2040)

* Dual-core processor
* Fast execution and low latency
* Raspberry Pi powered

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
| MOSI   | GPIO 11 |
| SCLK   | GPIO 10 |
| CS     | GPIO 9 |
| DC     | GPIO 8  |
| RST    | GPIO 12  |
| BL     | GPIO 13  |

---

### 💾 SD Card Support

* Read/write files from SD card  
* Store payloads, logs, and images  
* Used for dynamic content and scripting  

| Function | Pin |
|--------|-----|
| CS     | GPIO 17  |
| MOSI   | GPIO 19 |
| MISO   | GPIO 16 |
| SCLK   | GPIO 18 |

---

### 🌈 RGB LED

* WS2812 RGB LED support  
* Status indication and animations  

| Function | Pin |
|--------|------|
| Data   | GPIO 25 |

---


### 🧩 Modular Firmware Design

* Clean and reusable code structure  
* Separate modules for display, SD, HID, and wireless  
* Easy to expand and customize  

---

### 🛠 Developer Friendly

* Arduino + Circuit Python compatible  
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

<img width="900" height="700" alt="image" src="https://github.com/user-attachments/assets/8a71fb43-d10a-41aa-8224-1345b03317a7" />

---


### ⚙️ Step 5. Compile and Upload
Now you can uplaod the code to the BUG by clikcing the upload button in Arduino

---

## Library Requirements

Few Libraries are required to run the BUG-STM32, make sure they are pre-installed before running the examples
* ESP32 Arduino Core
* Required Libraries:
  * **Adafruit_GFX** - For animations
  * **Adafruit_ST7735** - For 0.96 TFT Display
  * **SD** - For SD Card
  * **Adafruit_NeoPixel** - For RGB LED
  * **SPI** - To run the SPI
 
---

## 📂 Examples

Explore ready-to-use examples:

| Example               | Description             |
| --------------        | ------------------------|
| 01_RGB_LED            | Glow Different RGB Patterns  |
| 02_LCD_TEST           | Display colors/lines/shapes |
| 03_Show_Image         | Show the BMP file image on the LCD - Not Completed yet |
| 04_Write_SDCard       | Write data to SD Card |
| 05_Notepad            | Open the notepad and write something to it using HID  |
| 06_Open_Website       | Check the website  |
| 07_ScanWiFi_Connect   | Scan the WiFi networks and connect to one of them  |
| 08_Create_Hotspot     | Create the Hotspot  |
| 09_Webpage            | Create the access point and open the webpage to control |

---

### ⚠️ Important Notes

- tft.setRotation(3) - This function is used to rotate the display

---

# 🛠 Getting Started with CircuitPython

### Step 1. Install circuitpython using thonny

1. Open **Thonny**  and press the boot button in **BUG-RP2040** and insert to the PC
2. Click on the right side corner and install the circuitpython
   <img width="1000" height="400" alt="image" src="https://github.com/user-attachments/assets/befae826-05fa-492b-8ef9-686eda3a3147" />


---

