#ifndef HARDWARE_H
#define HARDWARE_H

#include <WiFiClient.h>

void fetchHardwareData(const char* server, uint16_t port);
void displaySensorData(const String& name, const String& value);

#endif