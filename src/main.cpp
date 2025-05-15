#include "display/display.h"
#include "network/network.h"
#include "hardware/hardware.h"
#include "config.h"
#include "data.h"
#include "images.h"

const String OHM_SERVER = SERVER_URL;
const String OHM_PORT = "20000";

unsigned long lastUpdate = 0;
unsigned long lastServerCheck = 0;
const unsigned long SERVER_CHECK_INTERVAL = 10000;
const unsigned long RECONNECT_DELAY = 2000;

int counter = 0;
bool showCpu = true;
int connectionAttempts = 0;
const int MAX_CONNECTION_ATTEMPTS = 5;

void showConnectionScreen() {
  clearDisplay();
  // drawImage(epd_bitmap_POLARAS);
  showMessage("No Connection");
}

String getFirstWord(const String& str);

void ensureConnection() {
  showConnectionScreen();
  
  while (!isWiFiConnected() || !isServerReachable(OHM_SERVER.c_str(), OHM_PORT.toInt())) {
    connectToWiFi();
    delay(RECONNECT_DELAY);
    
    if (++connectionAttempts >= MAX_CONNECTION_ATTEMPTS) {
      ESP.restart();
    }
  }
  connectionAttempts = 0;
}

void setup() {
  Serial.begin(115200);
  initDisplay(false);
  
  showConnectionScreen();
  connectToWiFi();
  ensureConnection();
  
  if (isWiFiConnected()) {
    clearDisplay();
    showMessage(getIPv4().c_str());
    delay(3000);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastServerCheck >= SERVER_CHECK_INTERVAL) {
    lastServerCheck = currentMillis;
    
    if (!isWiFiConnected() || !isServerReachable(OHM_SERVER.c_str(), OHM_PORT.toInt())) {
      ensureConnection();
    }
  }

  if (currentMillis - lastUpdate >= 1000) {
    lastUpdate = currentMillis;

    if (isWiFiConnected() && isServerReachable(OHM_SERVER.c_str(), OHM_PORT.toInt())) {
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
}

String getFirstWord(const String& str) {
  int spaceIndex = str.indexOf(' ');
  return (spaceIndex == -1) ? str : str.substring(0, spaceIndex);
}