#include "hardware.h"
#include "network.h"
#include "display.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

void fetchHardwareData(const char* host, uint16_t port) {
  const String url = "http://" + String(host) + ":" + String(port) + "/data.json";
  
  if (!isServerReachable(host, port)) {
    showMessage("Server not reachable");
    return;
  }

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  String codeMsg = "HTTP CODE: " + String(httpCode);
  showMessage(codeMsg.c_str());
  delay(1500);
  
  if (httpCode > 0 )
  {
    String payload = http.getString();
    String message = "Payload: " + payload;
    showMessage(message.c_str());
  }
  http.end();
}
