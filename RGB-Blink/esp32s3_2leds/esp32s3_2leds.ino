#include <Arduino.h>
#include <math.h>

const int LED1_PIN = 6;
const int LED2_PIN = 7;

const uint32_t PWM_FREQ = 5000;   // 5 кГц, мерцания не видно
const uint8_t  PWM_BITS = 8;      // 0..255
const uint32_t PERIOD_MS = 3000;  // полный цикл «вдох-выдох»

// Гамма-коррекция: глаз воспринимает яркость нелинейно,
// без неё плавность заметна только на тёмном участке
uint8_t gamma8(float x) {         // x: 0.0..1.0
  return (uint8_t)(powf(x, 2.2f) * 255.0f + 0.5f);
}

void setup() {
  ledcAttach(LED1_PIN, PWM_FREQ, PWM_BITS);
  ledcAttach(LED2_PIN, PWM_FREQ, PWM_BITS);
}

void loop() {
  uint32_t t = millis() % PERIOD_MS;
  float phase = (float)t / PERIOD_MS * 2.0f * PI;

  // Синус превращаем из диапазона -1..1 в 0..1
  float b1 = (sinf(phase) + 1.0f) / 2.0f;
  float b2 = 1.0f - b1;           // противофаза

  ledcWrite(LED1_PIN, gamma8(b1));
  ledcWrite(LED2_PIN, gamma8(b2));

  delay(5);                       // ~200 обновлений в секунду
}