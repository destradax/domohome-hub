#include <Arduino.h>
#include <ESP8266WiFi.h>

#define RETRY_DELAY_MS 500
#define MAX_RETRIES 20

bool connectToWifi(const char* ssid, const char* passPhrase) {
  Serial.print("\nAttempting to connect to WiFi: ");
  Serial.print(ssid);
  Serial.print(" ...");

  WiFi.mode(WIFI_STA);
  WiFi.setHostname("domohome-hub");
  WiFi.begin(ssid, passPhrase);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < MAX_RETRIES) {
    delay(RETRY_DELAY_MS);
    Serial.print(".");
    retries++;
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Could not connect to WiFi");
    Serial.print("Current WiFi status: ");
    Serial.println(WiFi.status());
    Serial.println("WiFi diagnostic:");
    WiFi.printDiag(Serial);
    return false;
  }

  Serial.println("Connected ti WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  return true;
}