# 🏎️ Obstacle Avoiding Robot with ESP32, L298N & Ultrasonic Sensor

This project creates an **autonomous robot car** using an **ESP32**, an **L298N motor driver**, and an **HC-SR04 ultrasonic sensor**. It moves forward, detects obstacles, and automatically turns to avoid collisions.

## � Hardware Used

- **ESP32 development board**
- **L298N motor driver module**
- **HC-SR04 ultrasonic distance sensor**
- **4 DC motors** (2 left + 2 right — merged per side)
- **12V battery** (for motors)
- **Jumper wires**
- **4-wheel robot chassis**

> ✅ **Note:** Motors are wired in pairs (left/right), making it function like a 2-motor system.

---

## 🔌 Wiring Diagram

### 🛞 L298N Motor Connections
| Motor Pin | ESP32 GPIO | Function            |
|-----------|------------|---------------------|
| IN1       | 5          | Left motors forward |
| IN2       | 21         | Left motors reverse |
| IN3       | 18         | Right motors forward|
| IN4       | 19         | Right motors reverse|

### 📡 HC-SR04 Connections
| Sensor Pin | ESP32 GPIO | Function       |
|------------|------------|----------------|
| TRIG       | 15         | Trigger output |
| ECHO       | 2          | Echo input     |

> ⚠️ **Critical:** Connect all grounds (ESP32, battery, L298N, sensor) together.

---

## ⚡ Power Configuration
- **Motors:** 12V → L298N power terminals
- **ESP32:** USB or regulated 5V
- **Sensor:** 5V from ESP32/L298N

---

## 🧠 Behavior Logic

1. Sensor measures distance ahead
2. If clear (>20cm): Move forward
3. If obstacle (≤20cm):
   - Stop completely
   - Wait 500ms
   - Turn right for 600ms
   - Resume forward motion

---

## 📜 Function Summary

### `float getDistance()`
- **Returns:** Distance in cm (float)
- **Operation:** Triggers ultrasonic pulse and measures echo duration

### `void forward()`
- **Action:** Drives all motors forward
- **Pins Used:** IN1(High), IN3(High), others Low

### `void stopMotors()`
- **Action:** Cuts power to all motors
- **Pins Used:** All IN pins Low

### `void turnRight()`
- **Action:** Left motors forward, right motors stopped
- **Duration:** 600ms (hardcoded)
- **Pins Used:** IN1(High), others Low
