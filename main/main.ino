/*
  ------------------------------------------------------------------------------
  Project Title : Dual Joystick & Button Interface - Concept Prototype
  Author        : Matthew Evangelista
  Date Created  : July 20, 2025
  Version       : 1.0.1
  Platform      : Arduino Nano (ATmega328P)
  IDE           : Arduino IDE / PlatformIO

  Description:
    This program reads analog and digital signals from two independent joysticks 
    and three push buttons using direct register access for optimized performance.

    The analog inputs (A0–A3) are used for the X/Y axes of two thumb-style joysticks.
    Each analog reading is centered, scaled, and constrained to standard HID joystick
    output values ranging from -127 to +127, with a configurable deadzone to suppress
    minor drift/noise near the physical center.

    The digital inputs (D2–D5) read the button states using negative logic (active LOW),
    where each button is debounced using simple logic and internal pull-ups are enabled
    via direct manipulation of PORTD registers.

    Designed as a foundation for more complex HID emulation or PC/game controller 
    interfacing, this lightweight framework provides debug monitoring via Serial,
    and is optimized for rapid testing and easy future expansion.

  Hardware Used:
    - Arduino Nano (ATmega328P @ 16MHz)
    - 1x Dual-Axis Thumb Joystick Module (X/Y + button)
    - 3x Momentary Push Buttons

  Pin Mapping:
    - A0 (PC0) -> Joystick 1 X-Axis
    - A1 (PC1) -> Joystick 1 Y-Axis
    - A2 (PC2) -> Joystick 2 X-Axis
    - A3 (PC3) -> Joystick 2 Y-Axis
    - D2 (PD2) -> Joystick 1 Button
    - D3 (PD3) -> Button 1
    - D4 (PD4) -> Button 2
    - D5 (PD5) -> Button 3

  Configuration Flags:
    - TESTING: Adds delay between loop iterations for easier Serial monitoring
    - DEBUG  : Enables detailed Serial prints for all input states and scaled values
*/
#include <Arduino.h>

// System variables
//#define SCALING                   // Uncomment to implement Raw analog value scaling to other ranges. (Adjust scaling constants as needed.)
#define TESTING                     // Testing flag that slows serial print commands to make readable. Comment this out if fully implementing.'
#define DEBUG                       // Debug flag for serial prints to monitor. Comment out if when not needed. Seial print uses lots of esources.
#define bRate               0x2580  // Default baudrate for serial communication (9600)
#define delay_for_readings  0x3E8   // Default serial print timing to make reading outputs cleaner (1 sec / 1000ms).

// Analog Input Scaling Constants
#define ANALOG_DEADZONE      5      // Ignore small drift near center
#define ANALOG_CENTER        519    // Center point of joystick (ideal: 512)
#define ANALOG_MAX_INPUT     1023   // Max analogRead() value
#define ANALOG_OUTPUT_MIN    -127   // Minimum gamepad output value
#define ANALOG_OUTPUT_MAX    127    // Maximum gamepad output value

// Joystick PINs
#define JS1_X    14                 // PIN A0 - Joystick 1 x-axis 
#define JS1_Y    15                 // PIN A1 - Joystick 1 y-axis
#define JS2_X    16                 // PIN A2 - Joystick 2 x-axis
#define JS2_Y    17                 // PIN A3 - Joystick 2 y-axis

// Button PINs
#define js_btn   2                  // PIN D2 - Joystick 1 button
#define btn_1    3                  // PIN D3 - push button 1
#define btn_2    4                  // PIN D4 - push button 2
#define btn_3    5                  // PIN D5 - push button 3

// Prototype declarations
inline static int scaleAnalog(int val);  // Used to convert raw analog reading to standard game input via HID values.

void setup() {
  Serial.begin(bRate);

  // Configure Digital Inputs D2–D5 
  DDRD &= ~(1 << DDD2);    // D2 as input (Joystick Button)
  DDRD &= ~(1 << DDD3);    // D3 as input (Button 1)
  DDRD &= ~(1 << DDD4);    // D4 as input (Button 2)
  DDRD &= ~(1 << DDD5);    // D5 as input (Button 3)

  // Configure Analog Inputs A0–A3 (PC0–PC3)
  DDRC &= ~(1 << DDC0);    // A0 (Joystick 1 X)
  DDRC &= ~(1 << DDC1);    // A1 (Joystick 1 Y)
  DDRC &= ~(1 << DDC2);    // A2 (Joystick 2 X)
  DDRC &= ~(1 << DDC3);    // A3 (Joystick 2 Y)

  // --- ADC Reference Voltage ---
  analogReference(DEFAULT);  // Use AVcc (5V) as reference
  
  // Arduino framework to enable onboard pullups secondary to atmega chips
  // Even though we already configured registers manually above,
  // calling pinMode(..., INPUT_PULLUP) ensures compatibility across
  // libraries or future updates, and guarantees internal pullups are active.
  pinMode(js_btn, INPUT_PULLUP);
  pinMode(btn_1,  INPUT_PULLUP);
  pinMode(btn_2,  INPUT_PULLUP);
  pinMode(btn_3,  INPUT_PULLUP);

}

void loop(){
  // Read buttons (buttons use NPN logic | negative switching)
  bool button_js   = !(PIND & (1 << PIND2));  // Read D2 (Joystick button), LOW = pressed  
  bool button_1    = !(PIND & (1 << PIND3));  // Read D3
  bool button_2    = !(PIND & (1 << PIND4));  // Read D4
  bool button_3    = !(PIND & (1 << PIND5));  // Read D5

  // Read analog signals from joystick & potentiometers
  int js1_x = analogRead(JS1_X);  // A0
  int js1_y = analogRead(JS1_Y);  // A1
  int js2_x = analogRead(JS2_X);  // A2
  int js2_y = analogRead(JS2_Y);  // A3

  // Scale raw analog values from joystick & potentiometers
  int s_js1_x = scaleAnalog(js1_x);
  int s_js1_y = scaleAnalog(js1_y);
  int s_js2_x = scaleAnalog(js2_x);
  int s_js2_y = scaleAnalog(js2_y);

#ifdef DEBUG
  // Serial header
  Serial.println("==== Joystick & Button States ====");
  // Raw analog values
  Serial.println("Joystick 1 RAW X-Axis: " + String(js1_x));
  Serial.println("Joystick 1 RAW Y-Axis: " + String(js1_y));
  Serial.println("Joystick 2 RAW X-Axis: " + String(js2_x));
  Serial.println("Joystick 2 RAW Y-Axis: " + String(js2_y));
  
  #ifdef SCALING
    // Scaled analog values
    Serial.println("Scaled JS1 X: " + String(s_js1_x));
    Serial.println("Scaled JS1 Y: " + String(s_js1_y));
    Serial.println("Scaled JS2 X: " + String(s_js2_x));
    Serial.println("Scaled JS2 Y: " + String(s_js2_y));
  #endif // SCALING

  // Button states
  Serial.println("Joystick 1 Button: " + String(button_js));
  Serial.println("Button 1 state: " + String(button_1));
  Serial.println("Button 2 state: " + String(button_2));
  Serial.println("Button 3 state: " + String(button_3));
#endif // DEBUG

#ifdef TESTING
  delay(delay_for_readings);
#endif // TESTING
}

inline static int scaleAnalog(int val) {
  int delta = val - ANALOG_CENTER;
  if (abs(delta) < ANALOG_DEADZONE) return 0;

  return constrain((delta * ANALOG_OUTPUT_MAX) / (ANALOG_MAX_INPUT - ANALOG_CENTER),
                   ANALOG_OUTPUT_MIN, ANALOG_OUTPUT_MAX);
}



