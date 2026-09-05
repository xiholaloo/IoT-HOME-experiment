#include <Arduino.h>

const int LED_RED = 17;
const int LED_YELLOW = 16;
const int LED_GREEN = 4;
const int buttonPin = 2;

void NormalMode();

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void ButtonPressed() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed!");
    digitalWrite(LED_YELLOW, HIGH);
    delay(500);
    digitalWrite(LED_YELLOW, LOW);
    delay(500);
  }
}

void NormalMode() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  delay(5000);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  delay(2000);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(5000);
}

void loop() {
if (digitalRead(buttonPin) == LOW) {
    ButtonPressed();
  } else {
    NormalMode();
  }
}
