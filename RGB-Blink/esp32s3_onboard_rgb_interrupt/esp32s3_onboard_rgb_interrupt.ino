// ESP32-S3-DevKitC-1: две кнопки + ВСТРОЕННЫЙ RGB-светодиод (WS2812), ПРЕРЫВАНИЯ
// Кнопка 1 -> синий, кнопка 2 -> зелёный, обе -> голубой

const int BTN_BLUE  = 4;    // кнопка между GPIO и GND
const int BTN_GREEN = 5;    // кнопка между GPIO и GND

// Пин встроенного светодиода: v1.0 -> GPIO48, v1.1 -> GPIO38
#ifdef RGB_BUILTIN
  const int LED_PIN = RGB_BUILTIN;
#else
  const int LED_PIN = 48;   // для платы v1.1 поставьте 38
#endif

const uint8_t BRIGHT = 32;  // яркость 0..255 (на максимуме светодиод очень яркий)
const uint32_t DEBOUNCE_MS = 30;

volatile uint32_t lastEdge = 0;
volatile bool changed = false;

void IRAM_ATTR onButtonChange() {
  lastEdge = millis();
  changed = true;
}

void setLed(bool green, bool blue) {
  neopixelWrite(LED_PIN, 0, green ? BRIGHT : 0, blue ? BRIGHT : 0);
}

void setup() {
  pinMode(BTN_BLUE,  INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);
  setLed(false, false);

  attachInterrupt(digitalPinToInterrupt(BTN_BLUE),  onButtonChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN_GREEN), onButtonChange, CHANGE);
}

void loop() {
  if (changed && (millis() - lastEdge) > DEBOUNCE_MS) {
    changed = false;
    bool blue  = (digitalRead(BTN_BLUE)  == LOW);
    bool green = (digitalRead(BTN_GREEN) == LOW);
    setLed(green, blue);
  }
}
