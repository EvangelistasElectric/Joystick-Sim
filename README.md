📦 Dual Joystick & Button Interface – Concept Prototype
Author: Matthew Evangelista Version: 1.0.1 Date Created: July 20, 2025 Platform: Arduino Nano (ATmega328P) IDE: Arduino IDE / PlatformIO

🧠 Overview
This project provides a lightweight and efficient firmware for interfacing two analog joysticks (X/Y axes) and three push buttons with an Arduino Nano (ATmega328P). The code is optimized using direct register access for high-speed input reading and minimal overhead, making it ideal for game controller testing, robotics, or embedded interface development.

The firmware includes optional analog scaling to HID-compatible values and detailed serial debugging tools for monitoring input states in real time.

✨ Features
Reads 2 dual-axis analog joysticks via A0–A3

Reads 3 push buttons and a joystick button via D2–D5

Uses direct register access (DDRx, PORTx, PINx) for optimized performance

Internal pull-ups enabled on digital inputs

Optional analog scaling from raw 0–1023 to -127 to +127 with deadzone

Easily adjustable parameters via #define constants

Serial debug output with readable format

Modular and expandable design

🔧 Hardware Requirements
Arduino Nano (ATmega328P @ 16 MHz)

1x Dual-Axis Thumb Joystick Module

3x Momentary Push Buttons

(Optional) Additional joystick or potentiometers for simulation

🧬 Pin Mapping
Function	Pin	Register	Notes
Joystick 1 X-Axis	A0	PC0	Analog input
Joystick 1 Y-Axis	A1	PC1	Analog input
Joystick 2 X-Axis	A2	PC2	Analog input
Joystick 2 Y-Axis	A3	PC3	Analog input
Joystick 1 Button	D2	PD2	Digital input (LOW = pressed)
Button 1	D3	PD3	Digital input (LOW = pressed)
Button 2	D4	PD4	Digital input (LOW = pressed)
Button 3	D5	PD5	Digital input (LOW = pressed)
⚙️ Configuration Flags
These flags can be toggled at the top of the .ino file to enable or disable features:

DEBUG – Enables detailed serial printout of button and joystick states

TESTING – Adds delay for easier reading of serial output

SCALING – Enables analog value scaling for HID-style output

🎛️ Customization
Analog Scaling Parameters
Located at the top of the .ino file:

cpp
#define ANALOG_CENTER     519    // Center position of joystick
#define ANALOG_DEADZONE   5      // Ignore minor noise around center
#define ANALOG_OUTPUT_MIN -127   // Minimum scaled output
#define ANALOG_OUTPUT_MAX 127    // Maximum scaled output

🛡️ License
This project is licensed under the Evangelista's Electric Non-Commercial Open Source License (EENOSL).  
See [`LICENSE.txt`](./LICENSE.txt) for full terms.  

