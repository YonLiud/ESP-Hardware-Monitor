#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20
#include <ArduinoJson.h>
#include "hardware.h"

Temps parseHardwareData(const String& payload) {
  JsonDocument doc;  
  auto err = deserializeJson(doc, payload);
  if (err) {
    Serial.print(F("JSON error: "));
    Serial.println(err.f_str());
    return {};
  }

  const char* cpuTempCstr = doc["Children"][0]["Children"][1]["Children"][1]["Children"][0]["Value"].as<const char*>();

  const char* gpuTempCstr = doc["Children"][0]["Children"][3]["Children"][1]["Children"][0]["Value"].as<const char*>();

  const char* cpuNameCstr = doc["Children"][0]["Children"][1]["Text"].as<const char*>();

  const char* gpuNameCstr = doc["Children"][0]["Children"][3]["Text"].as<const char*>();

  return {
    String(cpuTempCstr),
    String(gpuTempCstr),
    String(cpuNameCstr),
    String(gpuNameCstr)
  };
}