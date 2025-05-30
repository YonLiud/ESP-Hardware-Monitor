#include "network.h"
#include "config.h"
#include <string>
#include <HTTPClient.h>

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned long startMillis = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() - startMillis > 15000) {
      Serial.println("Wi-Fi connection timeout!");
      return;
    }
  }
  Serial.println("Wi-Fi connected!");
}

String getIPv4() {
  return WiFi.localIP().toString();
}

String getIPv6() {
  return WiFi.localIPv6().toString();
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void checkWiFi() {
  if (!isWiFiConnected()) {
    connectToWiFi();
  }
}

bool isServerReachable(const char* host, uint16_t port) {
  WiFiClient client;
  return client.connect(host, port);
}

String getHardwareData(String ip, String port) {
  String url = "http://" + ip + ":" + port + "/data.json";
  HTTPClient http;
  http.begin(url);
  int code = http.GET();

  String payload;
  if(code == HTTP_CODE_OK) { 
    payload = http.getString();
  } else {
    Serial.printf("HTTP error: %d\n", code);
  }
  http.end();
  return payload;
}
