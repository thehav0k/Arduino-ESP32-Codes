// Motor pins
#define IN1 5
#define IN2 21
#define IN3 18
#define IN4 19

// Ultrasonic sensor pins (sensor at back)
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

  Serial.print("Front (via reverse) Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 20) {
    reverse();  // Move "forward" using reverse motion
  } else {
    stopMotors();
    delay(500);
    turnRight();  // Try turning when too close
    delay(600);
  }

  delay(100);
}

// Measure distance from ultrasonic sensor (mounted at back)
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;  // Convert to cm
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
