# 🤖 Smart Obstacle-Avoiding Robot with ESP32

This project is a **smart, autonomous robot** powered by an **ESP32** that avoids obstacles intelligently using an **ultrasonic sensor**, a **servo motor**, and **state-based decision logic**. It features **environment scanning**, **smart turning**, and **recovery mechanisms** when stuck.

---

## 🚀 Features

- Smooth obstacle avoidance using servo-mounted ultrasonic scanning
- Smart path decision using a scoring system
- Memory of past distance readings for noise reduction
- Recovery logic when stuck (multiple failed reverses)
- Debug-friendly `Serial Monitor` logs

---

## 🛠️ Components

| Component          | Quantity |
|--------------------|----------|
| ESP32 Dev Board    | 1        |
| L298N Motor Driver | 1        |
| DC Motors          | 4        |
| HC-SR04 Ultrasonic Sensor | 1  |
| Servo Motor (SG90 recommended) | 1 |
| Battery (6V-12V)    | 1        |
| Jumper Wires       | as needed |
| Chassis + Wheels   | 1 set    |

---

## 🧠 How It Works

1. **Default Movement**: The robot moves forward.
2. **Obstacle Detection**: When an object is detected closer than 30 cm, it stops.
3. **Environment Scan**: The servo rotates the ultrasonic sensor to check distances at multiple angles (30° to 150°).
4. **Path Selection**: It chooses the safest and most straight direction using a scoring algorithm.
5. **Stuck Detection**: If it keeps failing to move forward, it attempts recovery (reverse and turn).
6. **Loop**: The process repeats continuously.

---

## 📡 Wiring

| ESP32 Pin | Component         | Notes                  |
|-----------|------------------|------------------------|
| 5         | IN1 (Motor A)     | Motor control          |
| 18        | IN2 (Motor A)     | Motor control          |
| 19        | IN3 (Motor B)     | Motor control          |
| 21        | IN4 (Motor B)     | Motor control          |
| 25        | HC-SR04 TRIG      | Distance trigger       |
| 32        | HC-SR04 ECHO      | Distance echo          |
| 15        | Servo signal      | PWM output             |
| GND       | All grounds       | Common ground required |
| 5V        | HC-SR04 + Servo   | Power (separate 5V source recommended for motors) |

> 🔋 **Important:** Power motors using an external supply (not directly from ESP32 5V) to prevent resets.

---
