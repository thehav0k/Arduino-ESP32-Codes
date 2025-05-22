# 🤖 ESP32 Autonomous Reverse Car with Ultrasonic Sensor (Back Mounted)

This project implements a **self-navigating reverse-moving car** using an ESP32, L298N motor driver, and an ultrasonic sensor mounted at the **back**. The car safely reverses until it detects an obstacle behind it. It then stops and turns right to avoid collision.

---

## 🛠️ Components Required

- ESP32 development board
- L298N motor driver module
- 4x DC motors (chassis mounted)
- HC-SR04 ultrasonic distance sensor
- Power supply (7.4V to 12V recommended for motors)
- Jumper wires and breadboard (or soldered connections)
- Chassis (robot body)

---

## 🔌 Wiring Diagram

### Motor Driver (L298N) to ESP32

| L298N Pin     | ESP32 GPIO | Function                    |
|---------------|------------|-----------------------------|
| IN1           | GPIO 5     | Left motor direction        |
| IN2           | GPIO 21    | Left motor direction        |
| IN3           | GPIO 18    | Right motor direction       |
| IN4           | GPIO 19    | Right motor direction       |
| ENA / ENB     | Jumpered   | Enable left/right motors    |
| GND           | GND        | Common ground with ESP32    |
| 5V            | VIN of ESP32 (⚠️ Warning below) |

### Ultrasonic Sensor (HC-SR04) to ESP32

| HC-SR04 Pin | ESP32 GPIO | Description       |
|-------------|------------|-------------------|
| VCC         | 5V         | Power input       |
| GND         | GND        | Ground            |
| TRIG        | GPIO 15    | Trigger pin       |
| ECHO        | GPIO 2     | Echo pin          |

---

## ⚠️ ESP32 Power Warning

You can power the ESP32 via the 5V pin **only if**:
- L298N is powered from a 7.4–12V battery.
- The onboard 5V regulator is working and outputs a stable 5V.
- The 5V output is measured and verified before connecting to ESP32.

❌ **Do not connect unregulated 5V directly to ESP32** — it may damage the board.

---

## 🔁 Behavior Overview

- Car moves **in reverse** using `reverse()` function.
- An ultrasonic sensor on the **back** monitors rear distance.
- If distance drops below **20 cm**, the car:
  - Stops for 500ms
  - Turns right for 600ms
  - Resumes reversing
- Distance values are printed via the serial monitor.

---

## 📟 Serial Monitor Output

Run the Serial Monitor at **9600 baud** to see the following:

```text
Front (via reverse) Distance: 34 cm
Front (via reverse) Distance: 12 cm
Invalid distance reading. Skipping...
