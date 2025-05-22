# 🤖 ESP32 Obstacle-Avoiding Car (Sensor at Back)

This project creates a simple autonomous car using an **ESP32**, an **L298N motor driver**, and an **ultrasonic sensor mounted at the rear**. The car **moves in reverse as its primary motion**, checks the distance behind it, and **stops or turns right** if an obstacle is detected too close.

---

## 🛠️ Hardware Components

- ESP32 board
- L298N motor driver
- 4 DC motors (2 on each side)
- HC-SR04 ultrasonic sensor
- Power source (battery pack, 7.4V–12V)
- Jumper wires
- Chassis for mounting components

---

## 🔌 Wiring Connections

### 🔧 ESP32 to L298N Motor Driver

| L298N Pin     | ESP32 GPIO | Description              |
|---------------|------------|--------------------------|
| IN1           | GPIO 5     | Left motor direction 1   |
| IN2           | GPIO 21    | Left motor direction 2   |
| IN3           | GPIO 18    | Right motor direction 1  |
| IN4           | GPIO 19    | Right motor direction 2  |
| ENA (jumpered)| Powered    | Enable left motors       |
| ENB (jumpered)| Powered    | Enable right motors      |
| VCC           | 12V        | Motor power input        |
| GND           | Common GND | Connect to ESP32 GND     |
| 5V            | To ESP32 VIN | ⚠️ Only if safe (see power warning below) |

### 🔧 ESP32 to HC-SR04 Ultrasonic Sensor

| HC-SR04 Pin | ESP32 GPIO | Description       |
|-------------|------------|-------------------|
| VCC         | 5V         | Power supply      |
| GND         | GND        | Ground            |
| TRIG        | GPIO 15    | Trigger pin       |
| ECHO        | GPIO 2     | Echo response pin |

> 💡 **Sensor Mounting**: The ultrasonic sensor is mounted at the **back** of the car. The vehicle drives in **reverse**, using this sensor as a **"front-facing eye"**.

---

## ⚠️ Powering ESP32

You may power the ESP32 from the **5V pin of the L298N** only if:
- L298N is powered with 7.4V–12V on its VCC
- The onboard 5V regulator is present
- The **5V_EN jumper is installed**

### ❗ Warning:
- Measure voltage with a multimeter before connecting!
- Do **not** connect directly if 5V is unstable or unregulated.

---

## 🧠 Behavior

- The car **moves in reverse** by default.
- If the sensor (at the back) detects an object **closer than 20 cm**, the car:
  1. **Stops**
  2. **Waits 500ms**
  3. **Turns right** to avoid the obstacle
- Then resumes reverse driving.

---

## 📟 Serial Monitor Output

You can monitor the distance readings via the Serial Monitor at **9600 baud**:

```text
Front (via reverse) Distance: 34 cm
Front (via reverse) Distance: 12 cm
