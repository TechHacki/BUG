import board
import busio
import displayio
import digitalio
import fourwire
import storage
import sdcardio
import time

from adafruit_st7735r import ST7735R
from adafruit_display_text import label
import terminalio

# =================================================
# DISPLAY SETUP
# =================================================
displayio.release_displays()

spi_display = busio.SPI(board.GP10, MOSI=board.GP11)

display_bus = fourwire.FourWire(
    spi_display,
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
# UI SETUP
# =================================================
main_group = displayio.Group()
display.root_group = main_group

bg_bitmap = displayio.Bitmap(160, 80, 1)
bg_palette = displayio.Palette(1)
bg_palette[0] = 0x101820

bg = displayio.TileGrid(bg_bitmap, pixel_shader=bg_palette)
main_group.append(bg)

title = label.Label(terminalio.FONT, text="SD READER", color=0xFFFFFF)
title.x = 40
title.y = 15
main_group.append(title)

content_label = label.Label(terminalio.FONT, text="Loading...", color=0xFFFF00)
content_label.x = 10
content_label.y = 40
main_group.append(content_label)

# =================================================
# SD CARD SETUP (YOUR PINS)
# =================================================
spi_sd = busio.SPI(
    clock=board.GP18,
    MOSI=board.GP19,
    MISO=board.GP16
)

cs = board.GP17

# =================================================
# READ FILE FROM SD
# =================================================
try:
    content_label.text = "Mounting SD..."

    sdcard = sdcardio.SDCard(spi_sd, cs)
    vfs = storage.VfsFat(sdcard)
    storage.mount(vfs, "/sd")

    content_label.text = "Reading file..."
    time.sleep(1)

    with open("/sd/bug.txt", "r") as f:
        text = f.read()

    # Limit text so it fits LCD (simple truncation)
    if len(text) > 40:
        text = text[:40] + "..."

    content_label.text = text

except Exception as e:
    content_label.text = "SD ERROR"
    print("Error:", e)

# =================================================
# IDLE LOOP
# =================================================
while True:
    time.sleep(1)