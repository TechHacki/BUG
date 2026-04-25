import time
import board
import neopixel

# Configuration
PIXEL_PIN = board.GP25  
NUM_PIXELS = 1          
BRIGHTNESS = 0.3

pixels = neopixel.NeoPixel(
    PIXEL_PIN,
    NUM_PIXELS,
    brightness=BRIGHTNESS,
    auto_write=False
)

# Helper: set all pixels
def set_color(color):
    pixels.fill(color)
    pixels.show()

# Pattern 1: Blink Red
def blink_red(delay=0.5):
    set_color((255, 0, 0))
    time.sleep(delay)
    set_color((0, 0, 0))
    time.sleep(delay)

# Pattern 2: Color Cycle
def color_cycle(delay=0.3):
    colors = [
        (255, 0, 0),   # Red
        (0, 255, 0),   # Green
        (0, 0, 255),   # Blue
        (255, 255, 0), # Yellow
        (0, 255, 255), # Cyan
        (255, 0, 255), # Magenta
    ]
    for color in colors:
        set_color(color)
        time.sleep(delay)

# Pattern 3: Fade In/Out (single color)
def fade(color=(0, 0, 255), steps=50, delay=0.02):
    for i in range(steps):
        scale = i / steps
        pixels.fill(tuple(int(c * scale) for c in color))
        pixels.show()
        time.sleep(delay)
    for i in range(steps, -1, -1):
        scale = i / steps
        pixels.fill(tuple(int(c * scale) for c in color))
        pixels.show()
        time.sleep(delay)

# Pattern 4: Rainbow Cycle
def wheel(pos):
    if pos < 85:
        return (255 - pos * 3, pos * 3, 0)
    elif pos < 170:
        pos -= 85
        return (0, 255 - pos * 3, pos * 3)
    else:
        pos -= 170
        return (pos * 3, 0, 255 - pos * 3)

def rainbow_cycle(delay=0.01, cycles=1):
    for j in range(255 * cycles):
        for i in range(NUM_PIXELS):
            pixel_index = (i * 256 // NUM_PIXELS) + j
            pixels[i] = wheel(pixel_index & 255)
        pixels.show()
        time.sleep(delay)

# Main loop
while True:
    for _ in range(5):
        blink_red()

    for _ in range(3):
        color_cycle()

    for _ in range(2):
        fade((0, 0, 255))  # Blue fade

    rainbow_cycle()