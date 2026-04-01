# 🐞 BUG – STM32

## 🚀 Overview

BUG is a compact and powerful hardware platform designed for developers, makers, and hardware enthusiasts.
This repository contains the **STM32-based Arduino firmware** for BUG, providing a fast, stable, and flexible environment for building interactive embedded applications.

With integrated display, SD card support, and RGB feedback, BUG enables rapid development of user interfaces, data-driven applications, and portable tools.

---

## ✨ Features

### ⚡ High Performance (STM32F411CEU6)

* Fast execution and low latency
* Efficient memory usage
* Stable Arduino ecosystem support

### 📺 TFT Display (0.96" TFT)

* ST7735-based LCD support
* 0.96 TFT Display with 160x80 resolution
* Smooth UI rendering
* Text, graphics, and animation support
* Use Software SPI

 | Function | Pin |
 |--------|-----|
 | MOSI   | PB15 |
 | SCLK   | PB10 |
 | CS     | PB12 |
 | DC     | PB14 |
 | RST    | PB13 |
 | BL     | PB9  |
---

### 💾 SD Card Support

* Read/write files directly from SD card
* Store images, logs, and configuration data
* Perfect for dynamic content display
* Configure SPI1 pins manually

 | Function | Pin |
 |--------|-----|
 | CS     | PB6  |
 | MOSI   | PB5  |
 | MISO   | PB4  |
 | SCLK   | PB3  |
---

### 🌈 RGB LED

* WS2812 RGB LED support
* Status indication and animations
* Breathing and color-cycle effects

 | Function | Pin |
 |--------|------|
 | Data   | PC13 |

---

### 🔄 ST-Link Debug Connector

* On board 4 pin connector to connect with ST-Link
* Count Pin 1 from the button side as per the image

 | Function | Pin |
 |--------|--------|
 | PIN 1  | GND    |
 | PIN 2  | SWCLK  |
 | PIN 3  | SWDIO  |
 | PIN 4  | 3V3    |

![STM32_LINK](https://github.com/user-attachments/assets/e6c97faa-72a2-4a80-b235-3f60f9119eec)


<img width="700" height="400" alt="stm32Con" src="https://github.com/user-attachments/assets/dad540dc-0cee-41d2-ad22-e1a5d51f958a" />





---

### 🧩 Modular Firmware Design

* Clean and reusable code structure
* Separate modules for display, SD, and RGB
* Easy to expand and customize

---

### 🛠 Developer Friendly

* Simple Arduino-based workflow
* Well-structured examples
* Easy to modify and extend

---

# 🛠 Getting Started with Arduino

### Step 1. Install STM32 Board Support

1. Open **Arduino IDE**

2. Go to:
   `File → Preferences`

3. In **Additional Board Manager URLs**, add:

```
https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
```

4. Click **OK**

---

### Step 2. Install STM32 Core

1. Go to:
   `Tools → Board → Boards Manager`

2. Search for:

```
STM32
```

3. Install:

```
STM32 MCU based boards (by STMicroelectronics)
```

---

### ⚙️ Step 3. Select Board

For BUG (custom STM32 board):

```
Tools → Board → Generic STM32F4 series
```

---

### ⚙️ Step 4. Recommended Settings

USB Support - HID (Keyboard & Mouse)

Always use this setting for HID operations, without this BUG can't access the Keyboard & Mouse of the Computer.

| Setting       | Value                                     |
| -------------      | ----------------------------------|
| Board              | Generic STM32F4 series            |
| Board Part Number  | Generic F411CEUx                  |
| Upload Method      | STM32CubeProgrammer(DFU)          |
| USB Support        | HID (Keyboard & Mouse)            |

<img width="900" height="600" alt="image" src="https://github.com/user-attachments/assets/359fb262-1810-4eeb-b34a-a87d56c088ae" />

---

### ⚙️ Step 5. Compile and Upload
Now you can uplaod the code to the BUG by clikcing the upload button in Arduino

---

### 🔌 Step 6. Upload Methods

#### 🥉 USB (DFU Mode) (Recommended)

Press the button and insert BUG-STM32 USB Dongle to the computer and then open "Device Manager" you will see the STM32 board will pop-up in USB bootloader mode.

<img width="1000" height="600" alt="image" src="https://github.com/user-attachments/assets/cdda4e80-63bd-4895-8d14-ae5a11f9598a" />


Everytime you have to press the key to enter the USB-BOOTLOADER mode, so that you can directly program the STM32 without needing any external hardware.

---
#### 🥇 ST-Link

You can also use ST-Link to uplaod the code to your Bug device using STM32 Cube Programmer software. For more information about this software please check the link - https://www.st.com/en/development-tools/stm32cubeprog.html

For this you need the ST-Link dongle and connect the BUG using the connector.

![STM32_LINK](https://github.com/user-attachments/assets/fe9eb946-cdba-486d-8aa5-b3c0bddd83dd)


---


## Library Requirements

Few Libraries are required to run the BUG-STM32, make sure they are pre-installed before running the examples
* STM32 Arduino Core
* Required Libraries:
  * **Adafruit_GFX** - For animations
  * **Adafruit_ST7735** - For 0.96 TFT Display
  * **SD** - For SD Card
  * **Adafruit_NeoPixel** - For RGB LED
  * **SPI** - To run the SPI

---

## 📂 Examples

Explore ready-to-use examples:

| Example           | Description             |
| --------------    | ------------------------|
| 01_RGB_LED        | Different RGB Patterns  |
| 02_LCD_TEST       | Display colors/lines/shapes |
| 03_Show_Image_SD  | Read images from SD card and show on LCD |
| 04_Write_SDCard   | Write data to SD Card |
| 05_Notepad        | Open the notepad  |
| 06_Chrome_History | Check the chrome history  |
| 07_Open_Website   | Open a Website  |
| 08_Recycle_Bin    | Open Recycle Bin  |
| 09_Ducky_Example  | Read ducky style scripts from the SD card and run the scrips  |

---

## 📸 Ducky Style Scripts

**Example 09** - Read the ducky style scripts form the SD card and execute it. You can also create and save multiple scripts in the SD card and read/execute as per your choice. In this example we have created 'payload.txt' which is saved in the SD Card and it will open the notepad and write text to it.

🪟 Windows Example (Example-09 Script)
```
DELAY 2000
GUI
DELAY 2000
STRING notepad
ENTER
DELAY 2000
STRING Hello from Poopy
ENTER
```

🍎 macOS Example
```
DELAY 2000
CMD SPACE
DELAY 2000
STRING textedit
ENTER
```

🐧 Linux Example
```
DELAY 2000
CTRL ALT T
DELAY 2000
STRING nano demo.txt
ENTER
```
---

## 🪟 Windows / Linux / Mac OS (Update the Example as per OS in Arduino)

**Open Notepad in Windows**
```
Keyboard.press(KEY_LEFT_GUI); // CMD
delay(100);
Keyboard.releaseAll();

delay(1000);

Keyboard.print("notepad");
Keyboard.write(KEY_RETURN);
```

**Open TextEdit in macOS**
```
Keyboard.press(KEY_LEFT_GUI); // CMD
Keyboard.press(' ');
delay(100);
Keyboard.releaseAll();

delay(1000);

Keyboard.print("textedit");
Keyboard.write(KEY_RETURN);
```

**Open Nano Editor in Linux**
```
Keyboard.press(KEY_LEFT_CTRL); // CTRL + ALT + t
Keyboard.press(KEY_LEFT_ALT);
Keyboard.press('t');
delay(100);
Keyboard.releaseAll();

delay(1500);

Keyboard.print("nano demo.txt");
Keyboard.write(KEY_RETURN);
```
As per the operating system you have to update the code and use the shortcuts to open the tools. All the examples codes are developed for Windows OS but you can update the commands as per the OS.

---

### ⚠️ Important Notes

- SD card uses **hardware SPI1**, separate from display SPI  
- TFT uses **software SPI**, allowing flexible pin mapping
- Change tft.invertDisplay(true) to tft.color565(b, g, r) - to show real colors
- Change tft.initR(INITR_MINI160x80) to tft.initR(INITR_BLACKTAB) - Change to init the LCD with Black Color
- tft.setRotation(3) - This function is used to rotate the display
  
---


