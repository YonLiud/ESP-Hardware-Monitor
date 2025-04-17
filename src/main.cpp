#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"
#include "data.h"

const String OHM_SERVER = SERVER_URL;
const String OHM_PORT = "8085";

unsigned long lastUpdate = 0;
int counter = 0;
bool showCpu = true;

String firstWord(const String& str) {
  int spaceIndex = str.indexOf(' ');
  if (spaceIndex == -1) return str;
  return str.substring(0, spaceIndex);
}

void setup() {
  Serial.begin(115200);
  initDisplay();
  connectToWiFi();
  
  if (isWiFiConnected()) {
    String ipv4 = getIPv4();
    showMessage(ipv4.c_str());
  }

  delay(5000);
  clearDisplay();
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    String json = getHardwareData(OHM_SERVER, OHM_PORT);
    Temps temps = parseHardwareData(json.c_str());

    if (showCpu) {
      showTitle(firstWord(temps.cpuName).c_str());
      showTemp(temps.cpuTemp.c_str());
    } else {
      showTitle(firstWord(temps.gpuName).c_str());
      showTemp(temps.gpuTemp.c_str());
    }

    counter++;
    if (counter >= 5) {
      showCpu = !showCpu;
      counter = 0;
    }
  }
}