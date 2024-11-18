#include "SparkFun_iCap_OV5640.h"
#include "SparkFun_RP2_HSTX_ST7789_Arduino_Library.h"

// Configuration for the display
RP2_HSTX_ST7789_Config displayConfig = {
    .pinDin  =   18, // Must support HSTX (GPIO 12-19 on RP2350)
    .pinSck  =   19, // Must support HSTX (GPIO 12-19 on RP2350)
    .pinCs   =   16, // Must support HSTX (GPIO 12-19 on RP2350)
    .pinDc   =   17, // Must support HSTX (GPIO 12-19 on RP2350)
    .pinRst  =   -1, // Any GPIO pin, or -1 if not connected
    .pinBl   =   -1, // Any GPIO pin, or -1 if not connected
    .width   =  320, // Display width
    .height  =  240, // Display height
    .rawMode = true, // Whether to use raw mode
};

// Set up arch and pins structures for Pico RP2040.
iCap_arch arch =
{
    .pio = pio0, // Can be pio0, pio1, or pio2 on the RP2350
    .bswap = false // Whether to swap the camera data bytes
};

// Pins for the OV5640 camera
OV5640_pins pins =
{
    .enable = -1, // Any GPIO pin, or -1 if not connected
    .reset  = -1, // Any GPIO pin, or -1 if not connected
    .xclk   = 11, // Any GPIO pin
    .pclk   = 26, // Any GPIO pin
    .vsync  = 27, // Any GPIO pin
    .hsync  = 28, // Any GPIO pin
    .data   = {0, 1, 2, 3, 4, 5, 6, 7}, // Any GPIO pins, must be sequential!
    .sda    = 20, // Any I2C pin pair
    .scl    = 21  // Any I2C pin pair
};

// Create an instance of the camera
SparkFun_iCap_OV5640 cam(pins, &arch, Wire1);

// Create an instance of the display
RP2_HSTX_ST7789 display;

// Threshold pin
int thresholdPin = 22;

void setup() {
    Serial.begin(115200);
    Serial.println("Hello! Camera Test.");

    // Begin camera with QVGA resolution (320x240) and RGB565 color (16-bit)
    iCap_status status = cam.begin(OV5640_SIZE_QVGA, ICAP_COLOR_RGB565);
    while(status != ICAP_STATUS_OK)
    {
        Serial.println("Camera not found, please check wiring!");
        delay(1000);
    }

    // Initialize the display
    display.begin(displayConfig);

    // Set the threshold pin as an input with pull-up
    pinMode(thresholdPin, INPUT_PULLUP);
}

void loop()
{
    // Record the current time
    uint32_t t0 = micros();

    // Get the camera buffer
    uint16_t* buffer = cam.getBuffer();

    // Check whether thresholding is requested
    bool threshold = digitalRead(thresholdPin) != 0;

    // Send the command to start a new frame
    display.startNewFrameRaw();

    // Loop through all pixels in the frame buffer
    for (int y = 0; y < displayConfig.width; ++y)
    {
        for (int x = 0; x < displayConfig.height; ++x)
        {
            // Get the pixel value from the camera buffer
            int rgb = buffer[x * displayConfig.width + y];

            // Check whether thresholding is requested
            if(threshold)
            {
                // Extract the red, green, and blue components (RGB565)
                int r = (rgb >> 11) & 0x1f;
                int g = (rgb >> 5) & 0x3f;
                int b = rgb & 0x1f;

                // Calculate the sum of the components. Only use 5 bits of green
                // to match red and blue
                int sum = r + (g>>1) + b;

                // With 5 bits per channel, the maximum sum is 96, so we'll use
                // half of that as the threshold
                if(sum >= 48)
                {
                    // We're above the threshold, so set the pixel to white
                    rgb = 0xffff;
                }
                else
                {
                    // We're below the threshold, so set the pixel to black
                    rgb = 0x0000;
                }
            }

            // Send this pixel to the display
            display.putPixelRaw(rgb);
        }
    }

    // Record the current time
    uint32_t t1 = micros();

    // Print FPS of the display
    float fps = 1e6 / (t1 - t0);
    Serial.printf("Display FPS: %.2f\n", fps);
}
