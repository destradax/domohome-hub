#ifndef WIFI_H
#define WIFI_H

/// @brief Tries to connect to WiFi using the provided ssid and passPhrase
/// @param ssid 
/// @param passPhrase 
/// @return `true` if connection was successful, `false` otherwise
bool connectToWifi(const char* ssid, const char* passPhrase);

#endif