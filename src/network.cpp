#include "network.h"
#include "display.h"
#include "config.h"
#include <string>

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned long startMillis = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() - startMillis > 15000) { // Timeout after 15 seconds
      Serial.println("Wi-Fi connection timeout!");
      showMessage("Wi-Fi Timeout");
      return;
    }
  }
  Serial.println("Wi-Fi connected!");
  showMessage("Wi-Fi Connected!");
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

#include <WiFi.h>        // or <ESP8266WiFi.h> for ESP8266
#include <HTTPClient.h>

String getHardwareInfo(String ip, String port) {
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
