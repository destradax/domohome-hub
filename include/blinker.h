#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>

enum BlinkerStatus {
  BLINKER_STATUS_OFF,
  BLINKER_STATUS_IDLE,
  BLINKER_STATUS_ERROR
};

struct Stage {
  int ledStatus;
  unsigned long durationMs;
};

void initBlinker();
void setBlinkerStatus(BlinkerStatus status);
void blinkerLoop();

#endif