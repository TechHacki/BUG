import board
import displayio
import busio
import digitalio
import fourwire
import time
import usb_hid
import neopixel

from adafruit_st7735r import ST7735R
from adafruit_display_text import label
import terminalio

from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode
from keyboard_layout_win_uk import KeyboardLayout

# =================================================
# SELECT OS (UNCOMMENT ONE ONLY)
# =================================================
OS_MODE = "WINDOWS"
# OS_MODE = "MAC"
# OS_MODE = "LINUX"

# =================================================
# DISPLAY SETUP
# =================================================
displayio.release_displays()

spi = busio.SPI(board.GP10, MOSI=board.GP11)

display_bus = fourwire.FourWire(
    spi,
    command=board.GP8,
    chip_select=board.GP9,
    reset=board.GP12
)

display = ST7735R(
    display_bus,
    rotation=270,
    width=160,
    height=80,
    rowstart=1,
    colstart=26,
    invert=True
)

# Backlight
bl = digitalio.DigitalInOut(board.GP13)
bl.direction = digitalio.Direction.OUTPUT
bl.value = True

# =================================================
# UI
# =================================================
main_group = displayio.Group()

bg_bitmap = displayio.Bitmap(160, 80, 1)
bg_palette = displayio.Palette(1)
bg_palette[0] = 0x101820

bg = displayio.TileGrid(bg_bitmap, pixel_shader=bg_palette)
main_group.append(bg)

card_bitmap = displayio.Bitmap(140, 60, 1)
card_palette = displayio.Palette(1)
card_palette[0] = 0x1F6FEB

card = displayio.TileGrid(card_bitmap, pixel_shader=card_palette)
card.x = 10
card.y = 10
main_group.append(card)

title = label.Label(terminalio.FONT, text="OPENING", color=0xFFFFFF)
title.x = 45
title.y = 25
main_group.append(title)

subtitle = label.Label(terminalio.FONT, text="Google.com", color=0xFFFF00)
subtitle.x = 30
subtitle.y = 45
main_group.append(subtitle)

display.root_group = main_group

# =================================================
# NEOPIXEL
# =================================================
pixels = neopixel.NeoPixel(board.GP25, 12, brightness=0.1, auto_write=False)

def color_wipe(color, delay=0.02):
    for i in range(12):
        pixels[i] = color
        pixels.show()
        time.sleep(delay)

# =================================================
# HID
# =================================================
keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayout(keyboard)

time.sleep(2)

# =================================================
# PRE ANIMATION
# =================================================
for _ in range(2):
    color_wipe((255, 0, 0))
    color_wipe((0, 255, 0))
    color_wipe((0, 0, 255))

subtitle.text = "Launching..."

# =================================================
# OS-SPECIFIC LOGIC
# =================================================

# -------------------------------
# 🪟 WINDOWS
# -------------------------------
if OS_MODE == "WINDOWS":
    subtitle.text = "Windows Mode"

    # Open Run (Win + R)
    keyboard.press(Keycode.GUI, Keycode.R)
    keyboard.release_all()

    time.sleep(1)

    layout.write("https://www.google.com")
    time.sleep(0.3)

    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

# -------------------------------
# 🍎 macOS
# -------------------------------
elif OS_MODE == "MAC":
    subtitle.text = "macOS Mode"

    # Spotlight (CMD + SPACE)
    keyboard.press(Keycode.COMMAND, Keycode.SPACE)
    keyboard.release_all()

    time.sleep(1)

    # Open browser via command
    layout.write("open https://www.google.com")
    time.sleep(0.3)

    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

# -------------------------------
# 🐧 LINUX
# -------------------------------
elif OS_MODE == "LINUX":
    subtitle.text = "Linux Mode"

    # Open terminal (CTRL + ALT + T)
    keyboard.press(Keycode.CONTROL, Keycode.ALT, Keycode.T)
    keyboard.release_all()

    time.sleep(1.5)

    layout.write("xdg-open https://www.google.com")
    time.sleep(0.3)

    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

# =================================================
# FINAL STATE
# =================================================
subtitle.text = "Done ✔"

# LED loop
while True:
    for i in range(12):
        pixels[i] = (0, 50, 255)
    pixels.show()
    time.sleep(0.5)

    for i in range(12):
        pixels[i] = (0, 0, 0)
    pixels.show()
    time.sleep(0.5)