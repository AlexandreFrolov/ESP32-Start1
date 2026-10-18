// ESP32-S3-DevKitC-1-N16R8: встроенный RGB-светодиод (WS2812)
// GPIO48 - плата v1.0, GPIO38 - плата v1.1
#define RGB_PIN 48

void setup() {
  randomSeed(esp_random());   // аппаратный генератор случайных чисел
}

void loop() {
  uint8_t r, g, b;
  do {
    r = random(0, 256);
    g = random(0, 256);
    b = random(0, 256);
  } while (r + g + b < 100);  // отсекаем слишком тёмные цвета

  // Яркость уменьшена в 4 раза, светодиод очень яркий
  neopixelWrite(RGB_PIN, r / 4, g / 4, b / 4);

  delay(1000);
}