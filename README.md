# BusyBridge

<p align="center">
  <img src="https://img.shields.io/badge/version-1.0.0-blue" alt="Version">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="License">
  <img src="https://img.shields.io/badge/platform-ESP32--S2-red" alt="Platform">
  <img src="https://img.shields.io/badge/status-stable-success" alt="Status">
  <img src="https://img.shields.io/badge/tested-AGFEO%20Dashboard%20%7C%20Kuando%20HUB-brightgreen" alt="Tested">
</p>

<p align="center">
  <img src="Busybridge_prototype.jpg" alt="BusyBridge Prototype">
</p>

BusyBridge is an open-source ESP32-S2-based USB HID emulator that enables a Yealink BLT60 to operate as a Kuando-compatible Busylight.

The goal of this project is to reuse the inexpensive and widely available Yealink BLT60 as a drop-in replacement for an original Kuando Busylight by emulating the required USB HID protocol.

The project allows a Yealink BLT60 status light to be used with software that supports the original Kuando device, including AGFEO Dashboard and Kuando HUB.

---

## Features

- Emulates an original Kuando Busylight USB HID device
- Compatible with ESP32-S2
- Drives a Yealink BLT60 over its 2.5 mm connector
- Supports RGB colors
- Supports blinking status indications
- Supports status changes from host software
- Compatible with:
  - AGFEO Dashboard
  - Kuando HUB
- Open source

---

## Hardware

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

> **Note**
>
> The BLT60 uses a common-anode RGB configuration. All RGB channels are active-low and are driven directly from ESP32-S2 GPIO pins.

---

## How it Works

BusyBridge emulates the USB descriptors and HID reports of an original Kuando Busylight. To the host PC it appears as a genuine Kuando device while translating received color and status commands into LED control signals for the attached BLT60.

---

## Reverse Engineering Notes

USB descriptors, HID reports, identification responses and device behaviour were analyzed from an original Kuando Busylight to achieve software compatibility.

---

## Status

### Current Version

**v1.0.0**

Implemented and verified:

- USB enumeration
- HID communication
- Identity responses
- Color control
- Blink mode
- AGFEO Dashboard compatibility
- Kuando HUB compatibility

Real-world testing has confirmed successful operation with both AGFEO Dashboard and Kuando HUB.

---

## Building

### Build Environment

Tested with:

- Arduino IDE 2.x
- ESP32 Arduino Core 3.3.11
- ESP32-S2 Mini

Compile and flash the firmware to an ESP32-S2 board.

---

## Technical Notes

The Yealink BLT60 itself is a very simple device.

A teardown and electrical analysis showed that the BLT60 contains only two RGB LEDs connected in parallel. No microcontroller, USB interface, sound generator, buzzer or any other active electronics are present inside the unit.

All color control is performed externally through the four-wire connection:

- Common Anode (+3.3 V)
- Red LED channel
- Green LED channel
- Blue LED channel

---

## Why BusyBridge?

The BLT60 is widely available as surplus hardware and consists of little more than two RGB LEDs connected in parallel.

BusyBridge makes it possible to reuse this inexpensive hardware as a fully functional Kuando-compatible Busylight without modifying the BLT60 itself.

---

## Beyond the BLT60

### DIY KuandEmu

BusyBridge is not limited to the Yealink BLT60.

Because the project already emulates a Kuando-compatible USB HID device, it can also be used as the foundation for a completely custom Busylight implementation. Instead of connecting a BLT60, one or more WS2812 / NeoPixel LEDs can be attached to the ESP32-S2.

Combined with a custom enclosure, this creates a fully functional DIY Kuando-compatible Busylight, often referred to as **KuandEmu**.

Possible advantages include:

- Freely selectable enclosure design
- Adjustable brightness and LED count
- Custom shapes, light bars or desk indicators
- Easy integration into 3D-printed housings
- Low hardware cost
- Support for custom effects and animations

A simple ESP32-S2 combined with one or more WS2812 LEDs can therefore become a fully functional Kuando-compatible status indicator.

### WLED Integration

BusyBridge can also act as a bridge between Kuando-compatible software and existing WLED installations.

Instead of driving a local BLT60 or WS2812 LED, received status information can be forwarded over Wi‑Fi to one or more WLED controllers.

Example use cases include:

- LED strips behind a monitor
- Desk ambient lighting
- Office door status lights
- Workshop signal lighting
- Studio status indicators
- Entire room accent lighting

For example, when AGFEO Dashboard or Kuando HUB sets the Busylight status to red (busy), BusyBridge can forward the state to a WLED installation so that the entire workspace reflects the same status.

This extends BusyBridge beyond a simple hardware adapter and allows Kuando-compatible applications to interact with modern smart-lighting installations.

---

## Limitations Compared to an Original Kuando Busylight

Because of its simple hardware design, the BLT60 cannot reproduce certain features available on some original Kuando Busylight models.

- No acoustic signaling (buzzer)
- No audible notifications
- No internal USB electronics
- No onboard controller

Visual status indication through RGB LEDs is fully supported. Features that rely on an integrated buzzer are not available on BLT60 hardware.

---

## Contributions

Bug reports, testing feedback, pull requests and feature suggestions are welcome.

---

## License

Released under the MIT License.

Copyright (c) 2026 Swen Langel

See the LICENSE file for details.

---

## Support the Project

If you find BusyBridge useful and would like to support future development:

[![Buy Me a Coffee](giphy.gif)](https://buymeacoffee.com/retradnews)

☕ Buy me a coffee and help fund new hardware, testing equipment and future project development.

---

## Disclaimer

This project is not affiliated with, endorsed by, or sponsored by PLENOM, Kuando, Yealink or AGFEO.

All trademarks belong to their respective owners.
