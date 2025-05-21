# 🚗 4-Wheel Motor Control with ESP32 & L298N

This project demonstrates controlling a 4-wheel robot chassis using an ESP32, an L298N motor driver, and a 12V battery. The robot moves in different directions automatically in a timed sequence.

## 🧰 Hardware Required

- ESP32 development board
- L298N motor driver module
- 4-wheel robot chassis with 2 DC motors (left & right side)
- 12V battery (for motor power)
- Jumper wires

## 🔌 Pin Connections (ESP32)

| Motor Driver | ESP32 Pin | Function             |
|--------------|-----------|----------------------|
| IN1          | 5         | Left motor forward   |
| IN2          | 21        | Left motor backward  |
| IN3          | 18        | Right motor forward  |
| IN4          | 19        | Right motor backward |

> ✅ Make sure your ESP32 board supports all the listed GPIO pins.

## ⚡ Power Setup

- **Motor Power (12V):** Connect your 12V battery to the `VCC` and `GND` of the L298N module (do **not** power motors from the ESP32).
- **Logic Power (5V):** Use the onboard 5V output from the L298N to power the ESP32 (optional; use with caution and a voltage regulator if needed).
- Connect **all grounds together** (ESP32 GND to L298N GND and battery GND).

## 🧠 Code Behavior

The robot performs the following movements in a loop:
1. Moves **forward** for 2 seconds
2. Moves **backward** for 2 seconds
3. Turns **left** for 1 second
4. Turns **right** for 1 second
5. **Stops** for 2 seconds

## 📜 Function Overview

- `forward()`: Moves both motors forward
- `backward()`: Moves both motors backward
- `turnLeft()`: Runs only right motor forward
- `turnRight()`: Runs only left motor forward
- `stopMotors()`: Stops all motors

## 🚀 Upload Instructions

1. Open the `motor_control.ino` file in Arduino IDE or VS Code (PlatformIO).
2. Select the correct **ESP32 board** and COM port.
3. Click **Upload** to flash the code.

## 📁 File Name

Ensure your code file is named `motor_control.ino` and placed in a folder of the same name.

---

🔋 Powered by a 12V battery and controlled by an ESP32 for responsive robotic motion.
