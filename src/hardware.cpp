#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20
#include <ArduinoJson.h>

struct Temps {
  String cpu;
  String gpu;
};

std::pair<String, String> parseHardwareData(const String& payload) {
  JsonDocument doc;  
  auto err = deserializeJson(doc, payload);
  if (err) {
    Serial.print(F("JSON error: "));
    Serial.println(err.f_str());
    return {"", ""};  // return empty pair on error
  }

  // CPU: Children[0] → Children[1] → Children[1] → Children[0] → "Value"
  const char* cpuCstr = doc["Children"]
                           [0]
                           ["Children"]
                           [1]
                           ["Children"]
                           [1]
                           ["Children"]
                           [0]
                           ["Value"]
                           .as<const char*>();

  // GPU: Children[0] → Children[3] → Children[1] → Children[0] → "Value"
  const char* gpuCstr = doc["Children"]
                           [0]
                           ["Children"]
                           [3]
                           ["Children"]
                           [1]
                           ["Children"]
                           [0]
                           ["Value"]
                           .as<const char*>();

  return { String(cpuCstr), String(gpuCstr) }; // return as pair
}