# 🚗 ESP32 Bluetooth Controlled Car with LED Indicators

This project allows you to control a 4-wheel car using an **ESP32 with built-in Bluetooth**. It supports forward, reverse, left, right, and stop commands sent over Bluetooth. In addition, **LED indicators** are used for visual feedback based on the direction.

---

## 🛠️ Hardware Used

- ESP32 (with built-in Bluetooth)
- L298N Motor Driver
- 4 DC Motors (2 on left, 2 on right – wired in parallel)
- Red LED (for right turn indication)
- Green LED (for left turn indication)
- Power Source (Battery pack, 7.4V–12V)
- Jumper wires

---

## 🔌 Pin Configuration

### 🔧 ESP32 to Motor Driver (L298N):

| L298N Pin     | ESP32 GPIO | Description              |
|---------------|------------|--------------------------|
| IN1           | GPIO 5     | Left motor direction 1   |
| IN2           | GPIO 21    | Left motor direction 2   |
| IN3           | GPIO 18    | Right motor direction 1  |
| IN4           | GPIO 19    | Right motor direction 2  |
| ENA (jumpered)| Powered    | Enable left motors       |
| ENB (jumpered)| Powered    | Enable right motors      |
| VCC           | 12V        | Motor power supply       |
| GND           | Common GND | Shared with ESP32 ground |
| 5V            | To ESP32 VIN | ⚠️ Used to power ESP32 (see warning) |

### 💡 LED Connections:

| LED         | ESP32 GPIO | Behavior                     |
|-------------|------------|------------------------------|
| Red LED     | GPIO 2     | On when turning **right**    |
| Green LED   | GPIO 15    | On when turning **left**     |
| Both LEDs   | Blinking   | While moving **forward/reverse** |

---

## ⚠️ Powering ESP32 from L298N

You can power the ESP32 from the **5V pin** of the L298N **only if**:
- The L298N is supplied with 7.4–12V on `VCC`
- The onboard voltage regulator and **5V jumper are present**

> ❗ **Warning**: Always check the 5V pin voltage before connecting to the ESP32’s VIN. An unstable supply can damage your ESP32.

---

## 📱 Bluetooth Commands

Once connected via Bluetooth, send the following single-character commands:

| Command | Action     | LED Behavior                    |
|---------|------------|----------------------------------|
| `F`     | Forward    | Both LEDs blink                 |
| `B`     | Reverse    | Both LEDs blink                 |
| `L`     | Turn Left  | Green LED ON                    |
| `R`     | Turn Right | Red LED ON                      |
| `S`     | Stop       | Both LEDs OFF                   |

---

## 📲 How to Use

### On **Android**:
1. Install **Bluetooth Serial Controller** or **Serial Bluetooth Terminal** from Play Store.
2. Power on your ESP32 and search for Bluetooth devices.
3. Pair with the device named `ESP32-Car`.
4. Open the app, connect to `ESP32-Car`, and send commands using the terminal or custom buttons.

### On **iOS**:
> ⚠️ iOS does **not support Classic Bluetooth SPP**, which ESP32 uses by default.

#### To support iOS:
- Modify the project to use **Bluetooth Low Energy (BLE)**.
- Use apps like **nRF Connect** or **LightBlue Explorer** to communicate with BLE services.

---

## 🧠 How It Works

- The ESP32 listens for commands via Bluetooth.
- Based on the command, it drives the motors via the L298N driver.
- LEDs provide movement feedback:
  - Forward/Reverse → blink both LEDs.
  - Left turn → green LED ON.
  - Right turn → red LED ON.
  - Stop → all LEDs OFF.

---

## 📷 Demo

*(Add a picture or video showing the car and LED indicators in action)*

---

## 📎 Notes

- Make sure all grounds (motor power, ESP32, L298N) are connected.
- You can expand this project by adding more sensors (ultrasonic, IR, etc.) or moving to BLE for iOS support.
