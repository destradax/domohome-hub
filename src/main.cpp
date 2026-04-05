#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "credentials.h"
#include "wifi.h"

bool connectedToWifi = false;
bool printResult = true;

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  // initialize built-in led for blinking
  pinMode(LED_BUILTIN, OUTPUT);

  if (connectToWifi(ssid, passPhrase)) {
    connectedToWifi = true;
  }
}

void loop() {
  if (printResult) {
    printResult = false;

    if (connectedToWifi) {
      Serial.println("Hub connected to WiFi");
    } else {
      Serial.println("Hub did not connect to WiFi");
    }
  }
}