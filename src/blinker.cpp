#include <Arduino.h>
#include <blinker.h>

static bool initialized = false;

void initBlinker() {
  pinMode(LED_BUILTIN, OUTPUT);
  initialized = true;
}

void blink(unsigned long durationMs, unsigned long delayMs) {
  if (!initialized) return;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(durationMs);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayMs);
}

void blinkIdle() {
  blink(1000, 1000);
}