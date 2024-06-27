---
icon: material/cog
---

Let's take a closer look at the RP2350 and other hardware components on this Thing Plus board.

## RP2350 Microcontroller

## Raspberry Pi RM2 Radio Module

## Power Components

The Thing Plus - RP2350 includes several options for powering including USB-C, LiPo battery with on-board battery charging and monitoring circuits as well as direct power inputs.

### USB-C Connector

The USB-C connector on the board acts as the primary serial interface for the RP2350 as well as a power input. The <b>5V</b> USB input voltage is regulated down to <b>3.3V</b> through a voltage regulator with a max current of <b>500mA@3.3V</b>.

### 2-Pin JST Connector, Battery Charger, & Fuel Gauge

The board has a 2-pin JST connector to connect a single-cell Lithium Ion (LiPo) battery for battery-powered applications. It also has an MCP73831 battery charger to charge an attached battery and a MAX17048 fuel gauge to monitor battery voltage levels. The charge rate is set to <b>214mA@3.3V</b>. The MCP73831 receives power from the V_USB line so it only is powered when <b>5V</b> is provided either over USB or the V_USB PTH pin. If applying voltage directly to the V_USB pin make sure it does not exceed <b>5.5V</b>.

The MAX17048's I<sup>2</sup>C lines are pulled up to <b>3.3V_P</b> to allow for customizable power options. Read on below for more information about peripheral power.

## Peripheral Power Control

The board includes a second RT9080 3.3V regulator to control power to the peripheral 3.3V (3.3V_P) rail. This is powered on by default with some options for user control to help conserve power. The RT9080's EN (Enable) pin is tied to GPIO13 so users can drive it LOW in their code to disable this line. It also is tied to the main 3.3V rail through the <b>LP_CTL</b> solder jumper so it defaults to powered on. If this solder jumper is opened, it defaults to off when the RP2350 is power-cycled though users can drive the GPIO13 pin HIGH in their code to enable the 3.3V_P rail.

## Pinout & Qwiic Connector

Thing Plus boards break out a large number of GPIO and interface pins to a pair of 0.1"-spaced plated through-hole (PTH) headers and also has a Qwiic connector for easy integration into SparkFun's [Qwiic ecosystem](https://www.sparkfun.com/qwiic).

### Qwiic Connector

The Qwiic connector is tied to GPIO6 (SDA) and GPIO7 (SCL) pins on the RP2350. The Qwiic connector provides connections for SDA, SCL, 3.3V, and Ground. Note, the Qwiic connector power and I<sup>2</sup>C pins are tied to 3.3V_P and are powered by default but if the peripheral power control circuit is adjusted as covered above, it will not function properly without enabling 3.3V_P through code.

### PTH Headers

The Thing Plus's pair of PTH headers break out a selection of 21 GPIO pins from the RP2350 along with PTH connections to USB voltage (5V), regulated 3.3V, battery voltage, RP2350 reset signal, and the voltage regulator Enable pin.

## &micro;SD Card Slot

The board has a &micro;SD card slot that connects to the RP2350's SPI bus. Make sure the SPI are **LOW** when the &micro;SD card is **unpowered**. Setting these pins **HIGH** can damage the GPIO pins. The connector is a fricton-fit connector so no "clicking" and "unclicking" is necessary. Just plug it in nice and snug. 

## Buttons

There are two buttons on the board labeled <b>RESET</b> and <b>BOOT</b>. The RESET button is tied to the RP2350's RUN pin and resets the IC when pressed. The BOOT button puts the RP2350 into bootloader mode when held down during power on or reset.

<figure markdown>
[![Photo highlighting buttons.](./assets/img/Thing_Plus_ESP32S3-Buttons.jpg){ width="600"}](./assets/img/Thing_Plus_ESP32S3-Buttons.jpg "Click to enlarge")
</figure>

## LEDs

## Jumpers

??? note "Never modified a jumper before?"
	Check out our <a href="https://learn.sparkfun.com/tutorials/664">Jumper Pads and PCB Traces tutorial</a> for a quick introduction!
	<p align="center">
		<a href="https://learn.sparkfun.com/tutorials/664">
		<img src="https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/6/6/4/PCB_TraceCutLumenati.jpg" alt="Tutorial's thumbnail"><br>
        How to Work with Jumper Pads and PCB Traces</a>
	</p>


## Board Dimensions

The board dimensions are illustrated in the drawing below; the listed measurements are in inches.

<figure markdown>
[![Board Dimensions](../assets/img/dimensions.png){ width="400" }](../assets/img/dimensions.png "Click to enlarge")
<figcaption markdown>
[Board dimensions (PDF)](../assets/board_files/dimensions.pdf) for the <Product Name>, in inches.
</figcaption>
</figure>


??? tip "Need more measurements?"
	For more information about the board's dimensions, users can download the [Eagle files](../assets/board_files/eagle_files.zip) for the board. These files can be opened in Eagle and additional measurements can be made with the dimensions tool.

	??? info ":octicons-download-16:{ .heart } Eagle - Free Download!"
		Eagle is a [CAD]("computer-aided design") program for electronics that is free to use for hobbyists and students. However, it does require an account registration to utilize the software.

		<center>
		[Download from<br>:autodesk-primary:{ .autodesk }](https://www.autodesk.com/products/eagle/free-download "Go to downloads page"){ .md-button .md-button--primary width="250px" }
		</center>
	
	??? info ":straight_ruler: Dimensions Tool"
		This video from Autodesk demonstrates how to utilize the dimensions tool in Eagle, to include additional measurements:

		<center>
		<div class="video">
		<iframe src="https://www.youtube.com/embed/dZLNd1FtNB8" title="EAGLE Dimension Tool" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
		</div>
		</center>