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
# SELECT OS (CHANGE HERE)
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

title = label.Label(terminalio.FONT, text="TEXT MODE", color=0xFFFFFF)
title.x = 35
title.y = 25
main_group.append(title)

subtitle = label.Label(terminalio.FONT, text="Preparing...", color=0xFFFF00)
subtitle.x = 30
subtitle.y = 45
main_group.append(subtitle)

display.root_group = main_group

# =================================================
# NEOPIXEL
# =================================================
pixels = neopixel.NeoPixel(board.GP25, 12, brightness=0.1, auto_write=False)

def flash(color):
    pixels.fill(color)
    pixels.show()
    time.sleep(0.2)
    pixels.fill((0, 0, 0))
    pixels.show()

# =================================================
# HID
# =================================================
keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayout(keyboard)

time.sleep(2)

# =================================================
# PRE-FEEDBACK
# =================================================
flash((0, 0, 255))
subtitle.text = "Opening Editor..."

# =================================================
# OS-SPECIFIC ACTIONS
# =================================================

# -------------------------------
# 🪟 WINDOWS → Notepad
# -------------------------------
if OS_MODE == "WINDOWS":
    subtitle.text = "Windows"

    keyboard.press(Keycode.GUI, Keycode.R)
    keyboard.release_all()
    time.sleep(1)

    layout.write("notepad")
    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

    time.sleep(1)

    layout.write("hey I am BUG")

# -------------------------------
# 🍎 macOS → TextEdit
# -------------------------------
elif OS_MODE == "MAC":
    subtitle.text = "macOS"

    # Spotlight
    keyboard.press(Keycode.COMMAND, Keycode.SPACE)
    keyboard.release_all()
    time.sleep(1)

    layout.write("TextEdit")
    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

    time.sleep(1.5)

    layout.write("hey I am BUG")

# -------------------------------
# 🐧 LINUX → Nano (Terminal)
# -------------------------------
elif OS_MODE == "LINUX":
    subtitle.text = "Linux"

    # Open terminal
    keyboard.press(Keycode.CONTROL, Keycode.ALT, Keycode.T)
    keyboard.release_all()
    time.sleep(1.5)

    layout.write("nano")
    keyboard.press(Keycode.ENTER)
    keyboard.release_all()

    time.sleep(1)

    layout.write("hey I am BUG")

# =================================================
# FINAL STATE
# =================================================
subtitle.text = "Done ✔"

while True:
    flash((0, 255, 255))
    time.sleep(0.5)