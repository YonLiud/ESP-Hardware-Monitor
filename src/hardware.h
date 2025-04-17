#ifndef HARDWARE_H
#define HARDWARE_H

#include <array>
#include <WiFiClient.h>

// std::array<int, 3> fetchHardwareData(const char* server, uint16_t port);

std::pair<String, String> parseHardwareData(const String& payload);
void displaySensorData(const String& name, const String& value);

#endif