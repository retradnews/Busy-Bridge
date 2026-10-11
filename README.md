# BusyBridge

![Version](https://img.shields.io/badge/version-1.0.0-blueg.shields.io/badge/license-MIT-green
![Platformg.shields.io/badge/platform-ESP32--S2-red
![Status](https://img.shields.io/badge/statusccess
![Tested](https://img.shields.io/badge/tested-AGFEO%20Dashboard%20%7C%20Kuando%20HUBen

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

### Prototype

Busybridge_prototype.jpg

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
> The BLT60 uses a common-anode RGB configuration. All RGB channels are active-low and are driven directly
