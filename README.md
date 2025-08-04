# 📦 Dual Joystick & Button Interface – Concept Prototype

![Platform](https://img.shields.io/badge/platform-Arduino%20Nano-blue?logo=arduino)
![License](https://img.shields.io/badge/license-EENOSL-brightgreen)
![Status](https://img.shields.io/badge/status-Prototype-yellow)
![Language](https://img.shields.io/badge/language-C++-blue)

**Author:** Matthew Evangelista  
**Version:** 1.0.1  
**Date Created:** July 20, 2025  
**Platform:** Arduino Nano (ATmega328P)  
**IDE:** Arduino IDE / Arduino-CLI 

## 🛡️ License
This project is licensed under the Evangelista's Electric Non-Commercial Open Source License (EENOSL).
Please see LICENSE.txt for full terms.

---

## 🧠 Overview

This project provides a lightweight and efficient firmware for interfacing **two analog joysticks** (X/Y axes) and **three push buttons** with an Arduino Nano (ATmega328P).  
Using direct register access for minimal overhead, this system is ideal for game controller testing, robotics input, or embedded interface development.

Optional analog scaling supports HID-style output ranges, and serial debug tools provide real-time input feedback for development and testing.

---

## Video Links
Testing inputs via serial monitor: https://youtube.com/shorts/exbrDBUEC40 

Uploading program to board via Arduino IDE: https://youtu.be/AAV_ODUoQBg

---

## ✨ Features

- Reads 2 dual-axis analog joysticks via A0–A3  
- Reads 3 push buttons and 1 joystick button via D2–D5  
- Fast digital input reading using direct register access (DDRx, PORTx, PINx)  
- Internal pull-ups enabled on all digital inputs  
- Optional analog scaling from 0–1023 to -127 to +127 with adjustable deadzone  
- Adjustable parameters via `#define` constants  
- Serial debug output for real-time monitoring  
- Modular and expandable codebase

---

## 🔧 Hardware Requirements

- Arduino Nano (ATmega328P @ 16 MHz)  
- 1x Dual-Axis Thumb Joystick Module  
- 3x Momentary Push Buttons  
- *(Optional)* Additional joystick or potentiometers for simulation

---

## 🧬 Pin Mapping

| Function            | Pin | Register | Notes                       |
|---------------------|-----|----------|-----------------------------|
| Joystick 1 X-Axis   | A0  | PC0      | Analog input                |
| Joystick 1 Y-Axis   | A1  | PC1      | Analog input                |
| Joystick 2 X-Axis   | A2  | PC2      | Analog input                |
| Joystick 2 Y-Axis   | A3  | PC3      | Analog input                |
| Joystick 1 Button   | D2  | PD2      | Digital input (LOW = Pressed) |
| Button 1            | D3  | PD3      | Digital input (LOW = Pressed) |
| Button 2            | D4  | PD4      | Digital input (LOW = Pressed) |
| Button 3            | D5  | PD5      | Digital input (LOW = Pressed) |

---

## ⚙️ Configuration Flags

Toggle these flags in the source `.ino` file to enable/disable specific features:

- `DEBUG` – Enables detailed serial output of button and joystick states  
- `TESTING` – Adds delay between loop iterations for more readable serial output  
- `SCALING` – Enables scaling of analog inputs to HID-style output range

---

## 🎛️ Customization

**Analog Scaling Parameters** (modifiable at the top of the sketch):

```cpp
#define ANALOG_CENTER     519    // Center position of joystick
#define ANALOG_DEADZONE   5      // Ignore minor noise around center
#define ANALOG_OUTPUT_MIN -127   // Minimum scaled output
#define ANALOG_OUTPUT_MAX 127    // Maximum scaled output


