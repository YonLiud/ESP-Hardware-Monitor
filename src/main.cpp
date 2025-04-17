#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"
#include "data.h"

const char* OHM_SERVER = "192.168.1.119";
const uint16_t OHM_PORT = 8085;

void setup() {
  Serial.begin(115200);
  initDisplay();
  showMessage("Starting...");
  connectToWiFi();
  String message = "IPv4: " + getIPv4();
  showMessage(message.c_str());

  // delay(5000);
}

void loop() {
  delay(1000);
  parseHardwareData(payload.c_str());
}