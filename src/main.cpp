#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"

const char* OHM_SERVER = "192.168.1.119";
const uint16_t OHM_PORT = 8085;

void setup() {
  initDisplay();
  showMessage("Starting...");
  connectToWiFi();
  String message = getIPv4() + "\n" + getIPv6();
  showMessage(message.c_str());

  delay(5000);
}

void loop() {
  fetchHardwareData(OHM_SERVER, OHM_PORT);
  delay(5000);
}