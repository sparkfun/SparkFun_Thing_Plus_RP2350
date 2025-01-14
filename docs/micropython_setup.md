



## Setup

MicroPython is an application of the Python 3 language that runs on microcontrollers like the Thing Plus - RP2350 that allows you to easily interact with the board directly over a USB serial interface through either a command line interface or your preferred Python IDE such as [Thonny](https://thonny.org/). We'll do a quick overview of how to download MicroPython firmware on to the Thing Plus - RP2350 but for a complete overview of using MicroPython with this and other RP2350 boards, head over to Raspberry Pi's documentation by clicking the button below:

<center>
    [Raspberry Pi MicroPython Docs](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html){ .md-button .md-button--primary}
</center>

## UF2 Firmware

As of this writing, we're waiting on the next release of MicroPython to include UF2 files for the Thing Plus - RP2350 so to get users started before then, we have Beta releases of MicroPython firmware available [here](https://github.com/sparkfun/micropython/releases) or by clicking the button below:

<center>
    [SparkFun MicroPython Beta Releases](https://github.com/sparkfun/micropython/releases){ .md-button .md-button--primary}
</center>

Simply download the latest release and then put the Thing Plus - RP2350 into UF2 bootloader mode and open the location the board appeared as a USB storage device (it should appear as "RP2350"). Next, simply drag and drop the UF2 file into the RP2350 folder and the board should reboot. After the board reboots, open up your preferred MicroPython IDE (or command line interface) and you can start interacting with your Thing Plus. Read on to the MicroPython examples section for a few quick examples to make sure everything is working properly.