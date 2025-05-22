# 🚗 ESP32 Bluetooth Car with PWM Speed Control and LEDs

This project allows you to control a 4-wheel car using an ESP32 DevKit V1 with **inbuilt Bluetooth**, motor driver (L298N or similar), and adjustable speed using **PWM (Pulse Width Modulation)**. It also includes LED feedback for motion direction.

---

## 📦 Features

- Bluetooth control via Android serial terminal apps.
- PWM-based speed control (0-9 levels).
- Directional motion: Forward, Backward, Left, Right, Stop.
- LED indicators for motion status:
  - 🔴 Red LED for right turns
  - 🟢 Green LED for left turns
  - Blinking LEDs when moving forward or backward

---

## 📱 Bluetooth Setup

- **Module Used:** Inbuilt Bluetooth on ESP32 DevKit V1
- **Bluetooth Name:** `ESP32-Car`
- **App Suggestion (Android):**
  - Use **Bluetooth Terminal HC-05** or **Serial Bluetooth Terminal**
  - Connect to `ESP32-Car` and send single-character commands

> ⚠️ **iOS does not support Bluetooth Serial (Classic) with ESP32.**  
> To support iOS, consider using BLE or Wi-Fi-based control.

---

## 🎮 Controls

| Command | Action          | Notes                  |
|---------|-----------------|------------------------|
| `F`     | Move Forward     | Blinks both LEDs       |
| `B`     | Move Backward    | Blinks both LEDs       |
| `L`     | Turn Left        | Green LED ON           |
| `R`     | Turn Right       | Red LED ON             |
| `S`     | Stop             | Turns off LEDs         |
| `0-9`   | Set Speed        | 0 = min, 9 = max (0-225)|

Speed value = `number * 25`. (PWM range is 0–255)

---

## 🔌 Pin Connections

| ESP32 Pin | Function         | Connected To          |
|-----------|------------------|------------------------|
| 5         | Motor IN1 (PWM)  | L298N IN1              |
| 21        | Motor IN2 (PWM)  | L298N IN2              |
| 18        | Motor IN3 (PWM)  | L298N IN3              |
| 19        | Motor IN4 (PWM)  | L298N IN4              |
| 2         | Red LED          | (Optional LED + Resistor) |
| 15        | Green LED        | (Optional LED + Resistor) |
| 5V        | ESP32 Power      | From Regulated 5V Supply |
| GND       | Ground           | Common Ground with L298N and battery |

> ⚠️ **WARNING:** Do **NOT power ESP32 directly from L298N 12V motor supply.**
> Use a **separate 5V regulator (like AMS1117 or buck converter)** for safe power.

---

## ⚙️ PWM Setup on ESP32

This project uses **PWM (via `ledcWrite`)** for speed control:

- PWM Frequency: `5000 Hz`
- Resolution: `8-bit` (0–255)
- Speed steps: `0–9` mapped to `0–225`

The following pins are PWM-capable and used via `ledcAttach()`:
- IN1, IN2, IN3, IN4 (Pins: 5, 21, 18, 19)

---

## 🧠 How It Works

- On receiving a direction command, motors are driven via PWM at the last set speed.
- Speed is adjusted via numeric input `0`–`9`, immediately affecting motion.
- LEDs provide real-time feedback on turning or moving.

---

## 🛠️ Future Ideas

- Add OLED display for real-time status
- Manual/Autonomous mode switch
- Obstacle avoidance with ultrasonic sensor
- BLE or Wi-Fi control (for iOS support)

---

## 👤 Created by

- ESP32 DevKit V1 with Arduino
- Controlled via Android Bluetooth app
