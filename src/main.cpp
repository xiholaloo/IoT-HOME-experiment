#include <Arduino.h>

const int LED_RED = 17;
const int LED_YELLOW = 16;
const int LED_GREEN = 4;
const int buttonPin = 2;

enum NormalState {
  STATE_RED,
  STATE_YELLOW,
  STATE_GREEN
};

NormalState currentNormalState = STATE_RED;
unsigned long previousMillis = 0;
bool buttonPending = false;

void NormalMode();
void ButtonPressed();
void resetToNormalRed();

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);

  resetToNormalRed();
}

void resetToNormalRed() {
  currentNormalState = STATE_RED;
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  previousMillis = millis();
}

void ButtonPressed() {
  Serial.println("Button pressed!");

  // Ensure clean state: turn off other LEDs
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_YELLOW, HIGH);
    delay(500);
    digitalWrite(LED_YELLOW, LOW);
    delay(500);
  }

  digitalWrite(LED_RED, LOW);

  digitalWrite(LED_GREEN, HIGH);
  delay(5000);
  digitalWrite(LED_GREEN, LOW);

  // Wait for button release to prevent immediate re-triggering
  while (digitalRead(buttonPin) == LOW) {
    delay(10);
  }

  // Resume NormalMode starting at RED
  resetToNormalRed();
}

void NormalMode() {
  unsigned long currentMillis = millis();

  Serial.println(currentMillis);

  switch (currentNormalState) {
    case STATE_RED:
      if (currentMillis - previousMillis >= 5000) {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, HIGH);
        digitalWrite(LED_GREEN, LOW);
        currentNormalState = STATE_YELLOW;
        previousMillis = currentMillis;
      }
      break;

    case STATE_YELLOW:
      if (currentMillis - previousMillis >= 2000) {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_GREEN, HIGH);
        currentNormalState = STATE_GREEN;
        previousMillis = currentMillis;
      }
      break;

    case STATE_GREEN:
      if (currentMillis - previousMillis >= 5000) {
        if (buttonPending) {
          buttonPending = false;
          ButtonPressed();
        } else {
          digitalWrite(LED_RED, HIGH);
          digitalWrite(LED_YELLOW, LOW);
          digitalWrite(LED_GREEN, LOW);
          currentNormalState = STATE_RED;
          previousMillis = currentMillis;
        }
      }
      break;
  }
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !buttonPending) {
    buttonPending = true;
    Serial.println("Button press registered! Will execute after normal cycle finishes.");
  }

  Serial.println(previousMillis);

  NormalMode();
}
