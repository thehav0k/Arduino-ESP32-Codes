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

| Component                  | Quantity |
|---------------------------|----------|
| ESP32 Dev Board           | 1        |
| L298N Motor Driver        | 1        |
| DC Motors (2 per side)    | 4        |
| HC-SR04 Ultrasonic Sensor | 1        |
| Servo Motor (SG90)        | 1        |
| 12V Battery               | 1        |
| Jumper Wires              | as needed |
| 4-Wheel Chassis           | 1        |

---

## 🧠 How It Works

1. **Default Movement**: The robot moves forward.
2. **Obstacle Detection**: If an object is within 30 cm, it stops.
3. **Environment Scan**: The servo rotates the ultrasonic sensor to scan multiple angles (30°–150°).
4. **Path Selection**: A scoring algorithm chooses the safest and straightest direction.
5. **Smart Turning**: It turns based on the safest path.
6. **Stuck Detection**: If it repeatedly fails, it attempts recovery with reverse and turn.
7. **Loop**: The robot continues adapting and moving autonomously.

---

## 📡 Wiring

| ESP32 Pin | Component         | Notes                       |
|-----------|------------------|-----------------------------|
| 5         | IN1 (Left Motor)  | Motor A forward             |
| 18        | IN2 (Left Motor)  | Motor A backward            |
| 19        | IN3 (Right Motor) | Motor B forward             |
| 21        | IN4 (Right Motor) | Motor B backward            |
| 25        | TRIG (HC-SR04)    | Ultrasonic trigger          |
| 32        | ECHO (HC-SR04)    | Ultrasonic echo             |
| 15        | Servo Signal      | PWM signal to servo motor   |
| GND       | All Grounds       | Common ground (very important) |
| 5V        | Powered by L298N  | Connected from L298N 5V OUT |

---

## 🔌 Power Configuration

You are using a **12V battery** to power both:

- The **DC motors** through the **L298N motor driver**
- The **ESP32**, by connecting `5V OUT` from L298N to the ESP32's `5V` (Vin) pin

| Power Source   | Connected To                     | Notes                                                                 |
|----------------|----------------------------------|-----------------------------------------------------------------------|
| 12V Battery     | L298N `+12V` input                | Main power supply for motors and L298N                                |
| L298N `5V OUT` | ESP32 `5V` (Vin) pin              | Powers the ESP32 via onboard regulator                                |
| GND            | Common ground (ESP32, L298N, Sensors) | Must be connected together for stable operation                      |

> ⚠️ **Caution:**  
> While this works, L298N’s 5V regulator may be insufficient during WiFi use. If you face instability, use a **dedicated 5V buck converter (1A or more)** for the ESP32.

---

## 📘 User Manual

### 🔧 Setup Instructions

1. Assemble your robot chassis and mount the motors and wheels.
2. Connect your motor driver (L298N), ultrasonic sensor (HC-SR04), and servo motor to the ESP32 as per the wiring table.
3. Flash the provided Arduino code to your ESP32.
4. Power the system using a **12V battery** connected to the motor driver.

### 🕹️ Operating the Robot

- On startup, the robot will automatically start moving forward.
- It continuously monitors the distance in front.
- When it finds an obstacle:
  - It **stops**, **scans left and right**, and **decides** the best path.
  - If it can’t move forward for a few times, it tries to **reverse and turn**.
- Connect to the **Serial Monitor at 115200 baud** to see real-time debug output.

### 🔄 Reset & Restart

- Press the reset button on the ESP32 to restart the program.
- Turn off power before recharging or changing components.

---

