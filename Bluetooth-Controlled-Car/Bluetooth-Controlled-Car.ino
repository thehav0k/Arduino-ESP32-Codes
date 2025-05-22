#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// Motor pins
#define IN1 5
#define IN2 21
#define IN3 18
#define IN4 19

// LED pins
#define RED_LED 2
#define GREEN_LED 15

char command;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-Car");  // Bluetooth name

  // Motor pins setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // LED pins setup
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  stopMotors();
  turnOffLEDs();
  Serial.println("Bluetooth car ready. Connect and send commands.");
}

void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(command);

    switch (command) {
      case 'F': forward(); break;
      case 'B': reverse(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopMotors(); break;
    }
  }

  // LED effects during movement
  if (command == 'F' || command == 'B') {
    // Blink both LEDs for forward/reverse
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(200);
  }
}

// Motor movement functions
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void reverse() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  digitalWrite(RED_LED, HIGH);   // Red LED on for right turn
  digitalWrite(GREEN_LED, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH); // Green LED on for left turn
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  turnOffLEDs();
}

void turnOffLEDs() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}
