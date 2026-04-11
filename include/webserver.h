#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

bool handleFileRead(String path);
void handleNotFound();
void handleWifiStatus();

void initWebServer();

#endif
