#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"
#include "data.h"
#include "images.h"

// Configuration
const String OHM_SERVER = SERVER_URL;
const String OHM_PORT = "8085";

// Timing
unsigned long lastUpdate = 0;
unsigned long lastServerCheck = 0;
const unsigned long SERVER_CHECK_INTERVAL = 10000; // 10 seconds

// Display state
int counter = 0;
bool showCpu = true;

String getFirstWord(const String& str);

void showConnectionStatus() {
  clearDisplay();
  if (isWiFiConnected()) {
    showMessage(getIPv4().c_str());
  } else {
    showMessage("Connecting...");
  }
}

void ensureConnection() {
  clearDisplay();
  drawImage(epd_bitmap_POLARAS);
  
  while (!isWiFiConnected() || !isServerReachable(OHM_SERVER.c_str(), OHM_PORT.toInt())) {
    connectToWiFi();
    delay(2000);
    showConnectionStatus();
  }
}

void setup() {
  Serial.begin(115200);
  initDisplay(false);
  
  connectToWiFi();
  showConnectionStatus();
  delay(7000);
  
  ensureConnection();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastServerCheck >= SERVER_CHECK_INTERVAL) {
    lastServerCheck = currentMillis;
    ensureConnection();
  }

  if (currentMillis - lastUpdate >= 1000) {
    lastUpdate = currentMillis;

    String json = getHardwareData(OHM_SERVER, OHM_PORT);
    Temps temps = parseHardwareData(json.c_str());

    if (showCpu) {
      showTitle(getFirstWord(temps.cpuName).c_str());
      showTemp(temps.cpuTemp.c_str());
    } else {
      showTitle(getFirstWord(temps.gpuName).c_str());
      showTemp(temps.gpuTemp.c_str());
    }

    if (++counter >= 5) {
      showCpu = !showCpu;
      counter = 0;
    }
  }
}

String getFirstWord(const String& str) {
  int spaceIndex = str.indexOf(' ');
  return (spaceIndex == -1) ? str : str.substring(0, spaceIndex);
}