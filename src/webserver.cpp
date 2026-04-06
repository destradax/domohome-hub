#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "index_html.h"

ESP8266WebServer server(80);

/// @brief sends the index.html file
void handleRoot() { server.send(200, "text/html", index_html); }

/// @brief sends a JSON object with `ipAddress` and `hostname` properties
void handleWifiStatus() {
  JsonDocument doc;
  doc["ipAddress"] = WiFi.localIP().toString();
  doc["hostname"] = WiFi.getHostname();

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

/// @brief Initializes the web server and registers routes
void initWebServer() {
  LittleFS.begin();
  server.on("/", HTTP_GET, handleRoot);
  server.on("/wifi/status", HTTP_GET, handleWifiStatus);
  server.begin();
  Serial.println("Web server started");
}