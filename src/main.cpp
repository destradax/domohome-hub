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
  }
}

void loop() {
  if (connectedToWifi) {
    server.handleClient();
    blinkIdle();
  } else {
    blink(100, 100);
  }
}