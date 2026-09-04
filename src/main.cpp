#include <Arduino.h>

#define LED_RED 16
const int buttonPin = 2;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    Serial.println("Button pressed!"); 
      digitalWrite(LED_RED, HIGH);
  } else {
    Serial.println("Button released!");
    digitalWrite(LED_RED, LOW);
  }
}
