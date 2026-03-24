
# 🐞 BUG – STM32 Firmware

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

![STM32_LINK](https://github.com/user-attachments/assets/e6c97faa-72a2-4a80-b235-3f60f9119eec)


| Function | Pin |
|--------|--------|
| PIN 1  | GND    |
| PIN 2  | SWCLK  |
| PIN 3  | SWDIO  |
| PIN 4  | 3V3    |

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

## 📂 Repository Structure

```bash
firmware/BUG_Factory/   → Main production firmware  
firmware/core/          → Reusable modules  
examples/               → Feature-based demos  
docs/                   → Images, wiring, guides  
hardware/               → PCB and schematics  
tools/                  → Assets and utilities  
```

---

## 🛠 Getting Started

### 1️⃣ Requirements

* Arduino IDE
* STM32 Arduino Core
* Required Libraries:

  * Adafruit GFX
  * Adafruit ST7735
  * SD

---

### 2️⃣ Setup

1. Clone this repository:

```bash
git clone https://github.com/your-username/BUG-STM32-Arduino.git
```

2. Open:

```
firmware/BUG_Factory/BUG_Factory.ino
```

3. Select your STM32 board in Arduino IDE

4. Upload the code

---

### 3️⃣ First Run

On boot, BUG will:

* Initialize display
* Check SD card
* Show UI
* Run RGB effects
* Display scrolling content

---

## 📂 Examples

Explore ready-to-use examples:

| Example        | Description           |
| -------------- | --------------------- |
| 01_LCD_Test    | Display test          |
| 02_SD_Test     | SD card verification  |
| 03_RGB_Test    | RGB LED effects       |
| 04_Text_Scroll | Smooth scrolling text |
| 05_Full_Demo   | Complete system demo  |

---

## 📸 Demo

![Demo](docs/images/demo.gif)

---

## 🔌 Hardware Info

* MCU: STM32
* Display: ST7735 TFT
* Storage: SD Card
* LED: WS2812 RGB

See:
👉 `docs/wiring/` for pin configuration

---

## ⚠️ Notes

* Avoid using boot-sensitive pins for peripherals
* Ensure proper SD card wiring
* Use good quality USB cable for flashing

---

## 🧾 License

This project is licensed under the MIT License.

---

## ❤️ Support

If you like this project, consider supporting BUG on Kickstarter 🚀

---

## 👨‍💻 Contributing

Pull requests and ideas are welcome!
Help improve BUG and build something amazing together.




## 🔌 Pin Map (STM32 BUG)

### 📺 TFT Display (ST7735 – Software SPI)

| Function | Pin |
|--------|-----|
| MOSI   | PB15 |
| SCLK   | PB10 |
| CS     | PB12 |
| DC     | PB14 |
| RST    | PB13 |
| BL     | PB9  |

---

### 💾 SD Card (Hardware SPI1)

| Function | Pin |
|--------|-----|
| CS     | PB6  |
| MOSI   | PB5  |
| MISO   | PB4  |
| SCLK   | PB3  |

---

### 🌈 WS2812 RGB LED

| Function | Pin |
|--------|-----|
| Data   | PC13 |

---

### 🔌 USB

| Function | Description |
|--------|-------------|
| USB    | Programming & Power |

---

### ⚠️ Important Notes

- SD card uses **hardware SPI1**, separate from display SPI  
- TFT uses **software SPI**, allowing flexible pin mapping  
- Ensure proper power supply for stable SD card operation  
- WS2812 requires stable 5V/3.3V and proper grounding  

---

### 💡 Design Considerations

- Avoid reusing SPI pins for other peripherals  
- Keep SD card wiring short for stability  
- Use pull-up resistors if needed for reliable boot  

