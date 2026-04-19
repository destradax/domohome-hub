#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "blinker.h"
#include "credentials.h"
#include "webserver.h"
#include "wifi.h"

bool connectedToWifi = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  initBlinker();

  if (connectToWifi(ssid, passPhrase)) {
    connectedToWifi = true;
    initWebServer();
    setBlinkerStatus(BLINKER_STATUS_IDLE);
  } else {
    setBlinkerStatus(BLINKER_STATUS_ERROR);
  }
}

void loop() {
  blinkerLoop();

  if (connectedToWifi) {
    server.handleClient();
  }
}