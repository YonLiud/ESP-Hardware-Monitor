#include "hardware.h"
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 50
#include <ArduinoJson.h>

void parseHardwareData(const char* payload) {
  JsonDocument doc;  
  auto err = deserializeJson(doc, payload);
  if (err) {
    Serial.print(F("JSON error: "));
    Serial.println(err.f_str());
    return;
  }

  // CPU path: Children[0] → Children[1] → Children[1] → Children[0] → Value
  const char* cpuTemp = doc["Children"]
                            [0]
                            ["Children"]
                            [1]
                            ["Children"]
                            [1]
                            ["Children"]
                            [0]
                            ["Value"]
                            .as<const char*>();

  // GPU path: Children[0] → Children[3] → Children[1] → Children[0] → Value
  const char* gpuTemp = doc["Children"]
                            [0]
                            ["Children"]
                            [3]
                            ["Children"]
                            [1]
                            ["Children"]
                            [0]
                            ["Value"]
                            .as<const char*>();

  Serial.print(F("CPU Temperature: "));
  Serial.println(cpuTemp);

  Serial.print(F("GPU Temperature: "));
  Serial.println(gpuTemp);
}

