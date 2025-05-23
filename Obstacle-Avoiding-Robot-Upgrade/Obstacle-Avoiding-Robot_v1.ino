#include <ESP32Servo.h>

#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21
#define TRIG_PIN 25
#define ECHO_PIN 32
#define SERVO_PIN 15

Servo myServo;

// Navigation states
enum State { FORWARD, STOPPED, SCANNING, TURNING, REVERSING, STUCK };
State currentState = FORWARD;

// Constants
const int SCAN_ANGLES[] = {30, 60, 90, 120, 150}; // Scan multiple angles
const int NUM_SCANS = 5;
const float SAFE_DISTANCE = 30.0; // cm
const float CRITICAL_DISTANCE = 15.0; // cm
const int HISTORY_SIZE = 3; // For averaging sensor readings
const int STUCK_THRESHOLD = 3; // Number of reverses before stuck

// Variables
float distanceHistory[HISTORY_SIZE] = {0};
int historyIndex = 0;
int reverseCount = 0;
float distances[NUM_SCANS] = {0};
int lastTurnDirection = 0; // 1 for left, -1 for right, 0 for none

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

float getFilteredDistance() {
  float distance = getDistance();
  if (distance == -1) return distanceHistory[historyIndex]; // Use last valid reading
  distanceHistory[historyIndex] = distance;
  historyIndex = (historyIndex + 1) % HISTORY_SIZE;

  float sum = 0;
  int validCount = 0;
  for (int i = 0; i < HISTORY_SIZE; i++) {
    if (distanceHistory[i] > 0) {
      sum += distanceHistory[i];
      validCount++;
    }
  }
  return validCount > 0 ? sum / validCount : -1;
}

void forward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void reverse() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void turnLeft(int duration = 700) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  delay(duration);
  stopCar();
}

void turnRight(int duration = 700) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  delay(duration);
  stopCar();
}

void scanEnvironment() {
  for (int i = 0; i < NUM_SCANS; i++) {
    myServo.write(SCAN_ANGLES[i]);
    delay(200); // Reduced for faster scanning
    distances[i] = getFilteredDistance();
    Serial.print("Angle "); Serial.print(SCAN_ANGLES[i]);
    Serial.print(": "); Serial.print(distances[i]); Serial.println(" cm");
  }
  myServo.write(90); // Reset to front
  delay(200);
}

int findBestDirection() {
  float maxDistance = 0;
  int bestAngleIndex = 2; // Default to forward (90°)
  for (int i = 0; i < NUM_SCANS; i++) {
    float distance = distances[i] == -1 ? 1000 : distances[i]; // Treat -1 as far
    // Prioritize angles closer to forward (90°) by weighting distance
    float angleDiff = abs(SCAN_ANGLES[i] - 90);
    float score = distance * (1.0 - angleDiff / 180.0); // Higher score for straighter paths
    if (score > maxDistance) {
      maxDistance = score;
      bestAngleIndex = i;
    }
  }
  return bestAngleIndex;
}

void handleStuck() {
  Serial.println("Robot stuck! Initiating recovery...");
  reverse();
  delay(1000); // Longer reverse
  // Turn in the last successful direction or random if none
  if (lastTurnDirection == 1) {
    turnLeft(1000);
    Serial.println("Recovery: Turning Left");
  } else {
    turnRight(1000);
    Serial.println("Recovery: Turning Right");
  }
  reverseCount = 0; // Reset counter
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(90);
  delay(1000);

  Serial.println("Smart Bot Ready");
}

void loop() {
  float frontDistance = getFilteredDistance();
  Serial.print("Front: "); Serial.print(frontDistance); Serial.println(" cm");

  switch (currentState) {
    case FORWARD:
      if (frontDistance <= CRITICAL_DISTANCE && frontDistance != -1) {
        stopCar();
        currentState = STOPPED;
      } else {
        forward();
        if (frontDistance < SAFE_DISTANCE && frontDistance != -1) {
          currentState = SCANNING;
        }
      }
      break;

    case STOPPED:
      scanEnvironment();
      currentState = SCANNING;
      break;

    case SCANNING:
      {
        int bestDirection = findBestDirection();
        if (distances[bestDirection] < CRITICAL_DISTANCE && distances[bestDirection] != -1) {
          reverseCount++;
          if (reverseCount >= STUCK_THRESHOLD) {
            currentState = STUCK;
          } else {
            reverse();
            delay(800);
            currentState = STOPPED;
          }
        } else {
          reverseCount = 0; // Reset on clear path
          // Dynamic turn duration based on distance
          int turnDuration = map(distances[bestDirection], CRITICAL_DISTANCE, SAFE_DISTANCE, 1000, 500);
          turnDuration = constrain(turnDuration, 500, 1000);
          if (SCAN_ANGLES[bestDirection] < 90) {
            turnRight(turnDuration);
            Serial.println("Turning Right");
            lastTurnDirection = -1;
          } else if (SCAN_ANGLES[bestDirection] > 90) {
            turnLeft(turnDuration);
            Serial.println("Turning Left");
            lastTurnDirection = 1;
          } // If 90°, no turn needed
          currentState = FORWARD;
        }
      }
      break;

    case STUCK:
      handleStuck();
      currentState = STOPPED;
      break;

    default:
      currentState = STOPPED;
      break;
  }

  delay(100);
}
