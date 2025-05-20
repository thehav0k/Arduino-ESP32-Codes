# 🕹️ Mini Reaction Game (ESP32 + OLED + Ultrasonic + Servo)

A fun, interactive reaction timer game built on the ESP32 platform. Players must respond quickly by placing their hand near the ultrasonic sensor when prompted. Fast reactions earn a "win" with a servo movement reward, while delays result in a "too slow" response with a mocking servo movement and a fun bitmap graphic.

---

## 🎯 Features

- **OLED Display (SSD1306)** for game instructions and results.
- **Ultrasonic Sensor** (HC-SR04) to detect player response.
- **Servo Motor** for reward/punishment gestures.
- **Green and Blue LEDs** to indicate game states.
- Randomized wait time to ensure fairness.
- Cute bitmap character on failure for visual feedback.

---

## 🧰 Hardware Used

| Component             | Pin Connections                 |
|----------------------|----------------------------------|
| ESP32                |                                  |
| OLED Display (I2C)   | SDA → GPIO 33, SCL → GPIO 32     |
| Ultrasonic Sensor    | TRIG → GPIO 5, ECHO → GPIO 18    |
| Green LED            | GPIO 23                          |
| Blue LED             | GPIO 27                          |
| Servo Motor          | GPIO 2                           |

---

## 🚀 How It Works

1. Game shows **"Get Ready..."** message on the OLED.
2. After a random delay (2–6 seconds), **"GO!"** appears and the green LED turns on.
3. Player must quickly place their hand within **15 cm** of the ultrasonic sensor.
4. If the player reacts in time (within 500 ms), **"You Win!"** is shown and the servo rewards them.
5. If the player is too slow, **"Too Slow!"** appears, the blue LED lights up, a bitmap graphic is shown, and the servo mocks them.

---

## 🔧 Libraries Required

Make sure the following libraries are installed via the Arduino Library Manager:

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [ESP32Servo](https://github.com/jkb-git/ESP32Servo)

---

