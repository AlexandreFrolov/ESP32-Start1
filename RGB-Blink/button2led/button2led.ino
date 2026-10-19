#include <Arduino.h>

const int BTN1_PIN = 4;
const int BTN2_PIN = 5;
const int LED1_PIN = 6;
const int LED2_PIN = 7;

void setup() {
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED1_PIN, digitalRead(BTN1_PIN) == LOW);
  digitalWrite(LED2_PIN, digitalRead(BTN2_PIN) == LOW);
}