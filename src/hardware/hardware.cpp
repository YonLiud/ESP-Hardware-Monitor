#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20
#include <ArduinoJson.h>
#include "hardware.h"

String cleanTemp(const char* tempStr) {
  String temp = String(tempStr);
  int idx = temp.indexOf(" ");
  if (idx != -1) {
    temp = temp.substring(0, idx);
  }
  return temp;
}

Temps parseHardwareData(const String& payload) {
  JsonDocument doc;  
  auto err = deserializeJson(doc, payload);
  if (err) {
    Serial.print(F("JSON error: "));
    Serial.println(err.f_str());
    return {};
  }

  // to get the parsed json route use https://jsonformatter.org/json-parser

  const char* cpuTempCstr = doc["Children"][0]["Children"][1]["Children"][3]["Children"][0]["Value"].as<const char*>();

  const char* gpuTempCstr = doc["Children"][0]["Children"][3]["Children"][2]["Children"][0]["Value"].as<const char*>();

  const char* cpuNameCstr = doc["Children"][0]["Children"][1]["Text"].as<const char*>();

  const char* gpuNameCstr = doc["Children"][0]["Children"][3]["Text"].as<const char*>();
  return {
    cleanTemp(cpuTempCstr),
    cleanTemp(gpuTempCstr),
    String(cpuNameCstr),
    String(gpuNameCstr)
  };
}