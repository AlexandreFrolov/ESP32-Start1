// ESP32-S3-DevKitC-1: две кнопки + ВСТРОЕННЫЙ RGB-светодиод (WS2812), ОПРОС
// Кнопка 1 -> синий, кнопка 2 -> зелёный, обе -> голубой

const int BTN_BLUE  = 4;    // кнопка между GPIO и GND
const int BTN_GREEN = 5;    // кнопка между GPIO и GND

// Пин встроенного светодиода: v1.0 -> GPIO48, v1.1 -> GPIO38
#ifdef RGB_BUILTIN
  const int LED_PIN = RGB_BUILTIN;
#else
  const int LED_PIN = 48;   // для платы v1.1 поставьте 38
#endif

const uint8_t BRIGHT = 32;  // яркость 0..255
const uint32_t DEBOUNCE_MS = 30;

uint8_t lastRaw = 0;        // бит0 - синяя кнопка, бит1 - зелёная
uint8_t stable  = 0;
uint32_t lastChange = 0;

void setLed(bool green, bool blue) {
  neopixelWrite(LED_PIN, 0, green ? BRIGHT : 0, blue ? BRIGHT : 0);
}

void setup() {
  pinMode(BTN_BLUE,  INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);
  setLed(false, false);
}

void loop() {
  uint8_t raw = 0;
  if (digitalRead(BTN_BLUE)  == LOW) raw |= 0b01;
  if (digitalRead(BTN_GREEN) == LOW) raw |= 0b10;

  if (raw != lastRaw) {
    lastRaw = raw;
    lastChange = millis();
  }

  if (raw != stable && (millis() - lastChange) > DEBOUNCE_MS) {
    stable = raw;
    setLed(stable & 0b10, stable & 0b01);
  }

  delay(1);
}
