#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>

ESP8266WebServer server(80);

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";

  if (LittleFS.exists(path)) {
    String contentType = mime::getContentType(path);
    File file = LittleFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }

  return false;
}

void handleNotFound() {
  String uri = ESP8266WebServer::urlDecode(server.uri());

  if (!handleFileRead(uri)) {
    server.send(404, "text/plain", "FileNotFound");
  }
}

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

  // API routes
  server.on("/api/wifi/status", HTTP_GET, handleWifiStatus);

  // FS routes
  server.onNotFound(handleNotFound);

  server.enableCORS(true);
  server.begin();

  Serial.println("Web server started");
}