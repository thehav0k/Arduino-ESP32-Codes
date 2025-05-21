# 🚗 4-Wheel Motor Control Using L298N (Arduino)

This project controls a 4-wheel robot chassis using the L298N motor driver. The robot moves forward, backward, turns left and right, and stops in a loop.

## 🧰 Hardware Required

- Arduino (e.g., Uno, Nano, ESP32)
- L298N motor driver module
- 4-wheel robot chassis with 2 DC motors (left & right side)
- External power supply (for motors)
- Jumper wires

## 🔌 Pin Connections

| Motor Driver | Arduino Pin | Function             |
|--------------|-------------|----------------------|
| IN1          | 5           | Left motor forward   |
| IN2          | 21          | Left motor backward  |
| IN3          | 18          | Right motor forward  |
| IN4          | 19          | Right motor backward |

> ⚠️ Adjust the pin numbers if using a different board (e.g., Uno does not have pin 21 or 18).

## 🧠 How It Works

The robot performs the following sequence repeatedly:
1. Move **forward** for 2 seconds
2. Move **backward** for 2 seconds
3. Turn **left** for 1 second
4. Turn **right** for 1 second
5. **Stop** for 2 seconds

## 📜 Code Explanation

Functions:
- `forward()`: Both motors move forward.
- `backward()`: Both motors move backward.
- `turnLeft()`: Only right motor runs forward.
- `turnRight()`: Only left motor runs forward.
- `stopMotors()`: All motors stop.

## 🚀 Uploading the Code

1. Open the `.ino` file in Arduino IDE.
2. Select the correct board and COM port.
3. Click **Upload**.

## 📁 File

Save your code as `motor_control.ino` in a folder of the same name.

---

Made with ❤️ for robotics experimentation.
