#include <Arduino.h>
#include <blinker.h>

#define LED_ON LOW
#define LED_OFF HIGH

static bool initialized = false;
static BlinkerStatus currentStatus = BLINKER_STATUS_OFF;
static size_t currentStageIndex = 0;
static unsigned long stageStartTime = 0;

static const Stage offStages[] = {{LED_OFF, 0}};
static const size_t offStagesCount = 1;

static const Stage idleStages[] = {{LED_ON, 1000}, {LED_OFF, 3000}};
static const size_t idleStagesCount = 2;

static const Stage errorStages[] = {{LED_ON, 200}, {LED_OFF, 200},
                                    {LED_ON, 200}, {LED_OFF, 200},
                                    {LED_ON, 200}, {LED_OFF, 3000}};
static const size_t errorStagesCount = 6;

const Stage* getStatusStages(BlinkerStatus status) {
  switch (status) {
    case BLINKER_STATUS_OFF:
      return offStages;
    case BLINKER_STATUS_IDLE:
      return idleStages;
    case BLINKER_STATUS_ERROR:
      return errorStages;
    default:
      return offStages;
  }
}

const size_t getStatusStageCount(BlinkerStatus status) {
  switch (status) {
    case BLINKER_STATUS_OFF:
      return offStagesCount;
    case BLINKER_STATUS_IDLE:
      return idleStagesCount;
    case BLINKER_STATUS_ERROR:
      return errorStagesCount;
    default:
      return offStagesCount;
  }
}

void setBlinkerStatus(BlinkerStatus status) {
  currentStatus = status;
  currentStageIndex = 0;
  Stage currentStage = getStatusStages(currentStatus)[currentStageIndex];
  digitalWrite(LED_BUILTIN, currentStage.ledStatus);
  stageStartTime = millis();
}

void initBlinker() {
  pinMode(LED_BUILTIN, OUTPUT);
  setBlinkerStatus(BLINKER_STATUS_OFF);
  initialized = true;
}

void blinkerLoop() {
  if (!initialized) return;

  const Stage* currentStatusStages = getStatusStages(currentStatus);
  size_t currentStatusStageCount = getStatusStageCount(currentStatus);
  Stage currentStage = currentStatusStages[currentStageIndex];

  if (currentStage.durationMs == 0) {
    return;
  }

  unsigned long elapsed = millis() - stageStartTime;
  if (elapsed >= currentStage.durationMs) {
    currentStageIndex++;
    if (currentStageIndex >= currentStatusStageCount) {
      currentStageIndex = 0;
    }
    stageStartTime = millis();

    currentStage = currentStatusStages[currentStageIndex];
    digitalWrite(LED_BUILTIN, currentStage.ledStatus);
  }
}