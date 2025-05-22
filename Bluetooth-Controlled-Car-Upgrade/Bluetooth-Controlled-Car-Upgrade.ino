#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// Motor control pins
#define IN1 5
#define IN2 21
#define IN3 18
#define IN4 19

// LED pins
#define RED_LED 2
#define GREEN_LED 15

// PWM configuration
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8
#define SPEED_STEP 25

int speedValue = 250;
char command;
char currentMotion = 'S'; // Tracks the last motion state

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-Car");

  // Attach PWM to motor control pins
  ledcAttach(IN1, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(IN2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(IN3, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(IN4, PWM_FREQ, PWM_RESOLUTION);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  stopMotors();
  turnOffLEDs();
  Serial.println("Bluetooth car ready with PWM speed control.");
}

void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(command);

    switch (command) {
      case 'F': forward(); currentMotion = 'F'; break;
      case 'B': reverse(); currentMotion = 'B'; break;
      case 'L': turnLeft(); currentMotion = 'L'; break;
      case 'R': turnRight(); currentMotion = 'R'; break;
      case 'S': stopMotors(); currentMotion = 'S'; break;

      case '0' ... '9':
        speedValue = (command - '0') * SPEED_STEP;
        Serial.print("Speed set to: ");
        Serial.println(speedValue);
        updateMotion(); // Apply new speed immediately
        break;
    }
  }

  // Blinking LEDs while moving forward or reverse
  if (currentMotion == 'F' || currentMotion == 'B') {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(200);
  }
}

// Update motion based on currentMotion
void updateMotion() {
  switch (currentMotion) {
    case 'F': forward(); break;
    case 'B': reverse(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopMotors(); break;
  }
}

void forward() {
  ledcWrite(IN1, speedValue); ledcWrite(IN2, 0);
  ledcWrite(IN3, speedValue); ledcWrite(IN4, 0);
}

void reverse() {
  ledcWrite(IN1, 0); ledcWrite(IN2, speedValue);
  ledcWrite(IN3, 0); ledcWrite(IN4, speedValue);
}

void turnRight() {
  ledcWrite(IN1, speedValue); ledcWrite(IN2, 0);
  ledcWrite(IN3, 0);          ledcWrite(IN4, speedValue);
  digitalWrite(RED_LED, HIGH); digitalWrite(GREEN_LED, LOW);
}

void turnLeft() {
  ledcWrite(IN1, 0);          ledcWrite(IN2, speedValue);
  ledcWrite(IN3, speedValue); ledcWrite(IN4, 0);
  digitalWrite(RED_LED, LOW); digitalWrite(GREEN_LED, HIGH);
}

void stopMotors() {
  ledcWrite(IN1, 0); ledcWrite(IN2, 0);
  ledcWrite(IN3, 0); ledcWrite(IN4, 0);
  turnOffLEDs();
}

void turnOffLEDs() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}
