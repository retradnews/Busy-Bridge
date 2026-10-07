# BusyBridge

BusyBridge is an open-source ESP32-S2-based USB HID emulator that enables a Yealink BLT60 to operate as a Kuando-compatible Busylight.

The goal of this project is to reuse the inexpensive and widely available Yealink BLT60 as a drop-in replacement for an original Kuando Busylight by emulating the required USB HID protocol on an ESP32-S2.

The project allows a Yealink BLT60 status light to be used with software that supports the original Kuando device, including AGFEO Dashboard and Kuando HUB.

## Features

- Emulates an original Kuando Busylight USB HID device
- Compatible with ESP32-S2
- Drives a Yealink BLT60 over its 2.5 mm connector
- Supports RGB colors
- Supports blinking status indications
- Supports status changes from host software
- Successfully tested with:
  - AGFEO Dashboard
  - Kuando HUB
- Open source

## Hardware

## Prototype
 
![BusyBridge Prototype](Busybridge_prototype.jpg)

### Tested Hardware

- ESP32-S2 Mini
- Yealink BLT60

### BLT60 Wiring

| BLT60 Contact | Function / LED Color | ESP32 GPIO |
|--------------|---------------------|------------|
| Sleeve | Common Anode / 3.3 V | 3V3 |
| Tip | Red | GPIO18 |
| Ring1 | Green | GPIO17 |
| Ring2 | Blue | GPIO16 |

> Note:  
> The BLT60 uses a common-anode RGB configuration. All RGB channels are active-low and are driven directly from ESP32-S2 GPIO pins.

## How it Works

BusyBridge emulates the USB descriptors and HID reports of an original Kuando Busylight. To the host PC it appears as a genuine Kuando device while translating received color and status commands into LED control signals for the attached BLT60.

## Reverse Engineering Notes

USB descriptors, HID reports, device identification responses and device behaviour were analyzed from an original Kuando Busylight to achieve software compatibility.

## Status

### Current Version

**v1.0.0**

Current project status:

- USB enumeration working
- HID communication working
- Identity responses implemented
- Color control working
- Blink mode working
- AGFEO Dashboard compatible
- Kuando HUB compatible

Real-world testing has confirmed successful operation with both AGFEO Dashboard and Kuando HUB. Additional long-term and feature validation is ongoing.

## Building

### Build Environment

Tested with:

- Arduino IDE 2.x
- ESP32 Arduino Core 3.3.11
- ESP32-S2 Mini

Compile and flash the firmware to an ESP32-S2 board.

## Technical Notes

The Yealink BLT60 itself is a very simple device.

A teardown and electrical analysis showed that the BLT60 contains only two RGB LEDs connected in parallel. No microcontroller, USB interface, sound generator, buzzer or any other active electronics are present inside the unit.

All color control is performed externally through the four-wire connection:

- Common Anode (+3.3 V)
- Red LED channel
- Green LED channel
- Blue LED channel

## Why BusyBridge?

The BLT60 is widely available as surplus hardware and consists of little more than two RGB LEDs connected in parallel.

BusyBridge makes it possible to reuse this inexpensive hardware as a fully functional Kuando-compatible Busylight without modifying the BLT60 itself.

## Limitations Compared to an Original Kuando Busylight

Because of its simple hardware design, the BLT60 cannot reproduce certain features available on some original Kuando Busylight models.

- No acoustic signaling (buzzer)
- No audible notifications
- No internal USB electronics
- No onboard controller

Visual status indication through RGB LEDs is fully supported. Features that rely on an integrated buzzer are not available on BLT60 hardware.

## Contributions

Bug reports, testing feedback, pull requests and feature suggestions are welcome.

## License

Released under the MIT License.

Copyright (c) 2026 Swen Langel

See the LICENSE file for details.

[BuymeaCoffe](https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExeXo0dTEyancxaW1pc3MzOHZ1YWFnOWk0dzk1eGJlcmJsbmxwZWppbyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9cw/7kZE0z52Sd9zSESzDA/giphy.gif)

## Disclaimer

This project is not affiliated with, endorsed by, or sponsored by PLENOM, Kuando, Yealink or AGFEO.

All trademarks belong to their respective owners.
