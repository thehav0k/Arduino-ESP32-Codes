// Motor pins
#define IN1 5
#define IN2 21
#define IN3 18
#define IN4 19

// Ultrasonic sensor pins
#define TRIG_PIN 15
#define ECHO_PIN 2

long duration;
int distance;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopMotors();
  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  // Ignore invalid readings
  if (distance == -1) {
    Serial.println("Invalid distance reading. Skipping...");
    stopMotors();
    delay(200);
    return;
  }

  Serial.print("Front (via reverse) Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 20) {
    reverse();  // Safe to move
  } else {
    stopMotors();
    delay(500);
    turnRight();
    delay(600);
  }

  delay(100);
}

// Measure and filter ultrasonic distance
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout after 30ms (~5m max)

  if (duration == 0) return -1;  // No echo received

  int dist = duration * 0.034 / 2;

  // Filter out distances that are too small or too large
  if (dist < 2 || dist > 300) return -1;

  return dist;
}

// Movement functions
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void reverse() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
