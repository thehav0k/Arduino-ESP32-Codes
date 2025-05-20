#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 33
#define OLED_SCL 32

#define TRIG_PIN 5
#define ECHO_PIN 18

#define SERVO_PIN 2
#define GREEN_LED_PIN 23
#define BLUE_LED_PIN 27

TwoWire oledWire = TwoWire(1);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &oledWire, -1);
Servo myServo;

const unsigned char bitmap [] PROGMEM = {
  0b00000111, 0b11100000,
  0b00011111, 0b11111000,
  0b00111000, 0b00011100,
  0b01100100, 0b00100110,
  0b01001010, 0b01010010,
  0b11000000, 0b00000011,
  0b10100000, 0b00000101,
  0b10100000, 0b00000101,
  0b10101111, 0b11110101,
  0b10101111, 0b11110101,
  0b11010000, 0b00001011,
  0b01001000, 0b00010010,
  0b01100111, 0b11100110,
  0b00111111, 0b11111100,
  0b00001111, 0b11110000,
  0b00000000, 0b00000000
};

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  oledWire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(90);
}

void loop() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("Get Ready...");
  display.display();

  delay(random(2000, 6000));

  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("GO!");
  display.display();
  digitalWrite(GREEN_LED_PIN, HIGH);

  unsigned long startTime = millis();
  bool reacted = false;

  while (millis() - startTime < 500) {
    float distance = readDistanceCM();
    if (distance > 0 && distance < 15) {
      reacted = true;
      break;
    }
  }

  digitalWrite(GREEN_LED_PIN, LOW);
  display.clearDisplay();
  display.setCursor(0, 20);

  if (reacted) {
    display.println("You Win!");
    digitalWrite(GREEN_LED_PIN, HIGH);
    myServo.write(0);  // reward gesture
  } else {
    display.println("Too Slow!");
    digitalWrite(BLUE_LED_PIN, HIGH);
    display.drawBitmap(100, 20, bitmap, 16, 16, WHITE);
    myServo.write(180);  // mocking gesture
  }

  display.display();
  delay(3000);
  myServo.write(90);
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 20000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2;
}
