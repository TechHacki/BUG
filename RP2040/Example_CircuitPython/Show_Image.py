import board
import displayio
import busio
import digitalio
import fourwire
import time
from adafruit_st7735r import ST7735R

# =================================================
# DISPLAY SETUP
# =================================================
displayio.release_displays()

tft_dc   = board.GP8
tft_cs   = board.GP9        
tft_clk  = board.GP10
tft_mosi = board.GP11
tft_rst  = board.GP12

spi = busio.SPI(tft_clk, MOSI=tft_mosi)

display_bus = fourwire.FourWire(
    spi,
    command=tft_dc,
    chip_select=tft_cs,
    reset=tft_rst
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

# =================================================
# BACKLIGHT
# =================================================
tft_bl = board.GP13
backlight = digitalio.DigitalInOut(tft_bl)
backlight.direction = digitalio.Direction.OUTPUT
backlight.value = True


# =================================================
# SHOW IMAGE
# =================================================
bitmap_file = open("/BUG.bmp", "rb")  # KEEP FILE OPEN
bitmap = displayio.OnDiskBitmap(bitmap_file)

tile_grid = displayio.TileGrid(
    bitmap,
    pixel_shader=getattr(bitmap, "pixel_shader", displayio.ColorConverter())
)

image_group = displayio.Group()
image_group.append(tile_grid)
display.root_group = image_group


# =================================================
# MAIN LOOP
# =================================================
while True:
    pass