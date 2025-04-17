#ifndef HARDWARE_H
#define HARDWARE_H

#include <array>
#include <WiFiClient.h>

struct Temps {
    String cpuTemp;
    String gpuTemp;
    String cpuName;
    String gpuName;
};

Temps parseHardwareData(const String& payload);
void displaySensorData(const String& name, const String& value);

#endif