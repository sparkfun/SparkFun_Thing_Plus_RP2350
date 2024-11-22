



## Verify MicroPython Firmware & Hardware

First, to make sure everything is running properly, use the <code>sys</code> module to verify the firmware version and machine/board running. Open your preferred interface and enter the following prompts and you should see something similar to the printout below:

``` py
import sys
sys.implementation
(name='micropython', version=(1, 24, 0, 'preview'), _machine='SparkFun Thing Plus RP2350 with RP2350', _mpy=7942)
```

## Verify Memory (Internal and PSRAM)

Next, we can verify the total free memory on the Thing Plus which includes the built-in memory on the RP2350 as well as the 8MB PSRAM. We'll use the <code>gc</code> module for this so type in the prompt below and you should see a response close to the value below:

``` py
import gc
gc.mem_free()
8640352
```

## WS2812 LED Control

Now let's make sure we can properly control the WS2812 LED on the Thing Plus using the <code>machine</code> and <code>neopixel</code> classes. The WS2812 Data In pin connects to I/O 14 but we've defined this pin as <b>"NEOPIXEL"</b> which takes care of assigning the pin and defining it as an output. Next, we'll set the color to red and finally write the color values to the LED. The code below goes through all these steps so try copying it on your machine and you should see the WS2812 LED turn red.

``` py
import machine, neopixel
pin = machine.Pin("NEOPIXEL")
led = neopixel.NeoPixel(pin, 1)
led[0] = (255, 0, 0)
led.write()
```

Try playing around with other values between 0 and 255 for the three colors (R, G, B) and then writing the changes to switch the LED's displayed color.

## Network Test

Finally, let's run an example to test connecting the Thing Plus - RP2350 to a WiFi network, then access an API and print out the data returned. This example polls a database maintained [here](https://corquaid.github.io/international-space-station-APIs/JSON/people-in-space.json) that lists the number and names of astronauts currently on the ISS and then prints them out. The code also includes some helpful RGB status colors to indicate when the board is connecting to WiFi (RED), downloading data (BLUE), and on success (GREEN).

Before running the example, adjust the template values in the example called <code>WIFI_NETWORK</code> and <code>WIFI_PASSWORD</code> with your WiFi network ID and password.

``` py
import network
import urequests
import time
import neopixel
import machine

# Set up the NeoPixel LED
pin = machine.Pin("NEOPIXEL")
led = neopixel.NeoPixel(pin, 1)

# Set the LED to red while connecting to WiFi
led[0] = (255, 0, 0)
led.write()

# Connect to a WiFi network
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect('WIFI_NETWORK', 'WIFI_PASSWORD')

# Wait for the connection to complete
print("Waiting for connection...")
while not wlan.isconnected():
	time.sleep(1)
	print('.', sep='', end='', )
print('Connected!')

# Set the LED to blue while downloading data
led[0] = (0, 0, 255)
led.write()

# Download the list of astronauts currently in space
print('Downloading list of astronauts currently in space...')
astronauts = urequests.get("https://corquaid.github.io/international-space-station-APIs/JSON/people-in-space.json").json()

# Print the number of astronauts and their names
number = astronauts['number']
print('There are', number, 'astronauts in space.')
for i in range(number):
    print(i+1, astronauts['people'][i]['name'])

# Set the LED to green to indicate success
led[0] = (0, 255, 0)
led.write()

```
