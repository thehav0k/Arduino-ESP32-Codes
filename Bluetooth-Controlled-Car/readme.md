
# 🚗 ESP32 Bluetooth Controlled Car

This project allows you to control a 4-wheel car using an ESP32 and its **built-in Bluetooth**. You can send commands from your phone using any **Bluetooth Serial Terminal** app to move the car forward, reverse, turn, or stop.

---

## 🛠️ Hardware Used

- ESP32 (with built-in Bluetooth)
- L298N Motor Driver
- 4 DC Motors (2 on left, 2 on right – wired in parallel)
- Power Source (Battery pack, e.g. 2S Li-ion 7.4V–12V)
- Jumper wires

---

## 🔌 Motor Driver Connections

Connect the L298N motor driver to the ESP32 as follows:

| L298N Pin     | ESP32 GPIO | Description              |
|---------------|------------|--------------------------|
| IN1           | GPIO 5     | Left motor direction 1   |
| IN2           | GPIO 21    | Left motor direction 2   |
| IN3           | GPIO 18    | Right motor direction 1  |
| IN4           | GPIO 19    | Right motor direction 2  |
| ENA (jumpered)| Powered    | Left motor enable        |
| ENB (jumpered)| Powered    | Right motor enable       |
| VCC           | 12V        | Motor power supply       |
| GND           | Common GND | Shared with ESP32 ground |
| 5V            | To ESP32 VIN | **⚠️ Used to power ESP32** (see warning below) |

> 🧠 **Motor Wiring Tip:**  
> Connect motors in parallel:  
> - Left side motors → OUT1 and OUT2  
> - Right side motors → OUT3 and OUT4

---

## ⚠️ Powering ESP32 from L298N

You can use the **5V output from the L298N to power the ESP32** by connecting it to the **VIN pin** of the ESP32 **only if**:
- The L298N is supplied with 7.4V–12V on its `VCC` pin
- The onboard 5V regulator is present and the **5V_EN jumper is installed**

### ❗ Warning:
- **Always measure the 5V pin with a multimeter** before connecting to ESP32.
- Do **not** use the 5V pin if your L298N has no regulator or the 5V jumper is removed.
- ESP32 can be damaged by unstable or incorrect voltage levels.

---

## 📱 Bluetooth Commands

Once connected via Bluetooth, send the following single-character commands:

| Command | Action     |
|---------|------------|
| `F`     | Forward    |
| `B`     | Reverse    |
| `L`     | Turn Left  |
| `R`     | Turn Right |
| `S`     | Stop       |

---

## 📲 How to Use

### On **Android**:
1. Install **Bluetooth Serial Controller** or **Serial Bluetooth Terminal** from the Play Store.
2. Power on your ESP32 and search for Bluetooth devices.
3. Pair with the device named `ESP32-Car` (default name).
4. Open the app, connect to `ESP32-Car`, and use the terminal or button panel to send commands.

### On **iOS**:
> ⚠️ iOS does **not support Classic Bluetooth SPP (Serial Port Profile)**, which ESP32 uses by default.

#### Alternatives for iOS:
- **Use a Bluetooth Low Energy (BLE) solution**:
  - Modify the code to use BLE instead of Serial Bluetooth.
  - Use a compatible app like **LightBlue Explorer** or **nRF Connect** to interact with your ESP32 BLE services.

> 🛠️ BLE is more iOS-compatible, but requires more complex setup and coding.

---

## 🧠 Code Summary

The ESP32 listens for a character via Bluetooth and drives the motors accordingly using digital signals to the L298N driver. Motor direction is controlled by setting the proper logic levels to the input pins.

---

## 📷 Preview / Demo

*(Add images or videos of your car in action here)*

---

## 📎 Notes

- Ensure motor power supply is separate from ESP32 USB power (unless safely using 5V from L298N).
- Be cautious while testing — the car may move quickly on hard surfaces.
