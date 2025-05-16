#include "display/display.h"
#include "network/network.h"
#include "hardware/hardware.h"
#include "config.h"
#include "data.h"
#include "images.h"

unsigned long lastUpdate = 0;
const String OHM_SERVER = SERVER_URL;
const String OHM_PORT = "20000";

String getFirstWord(const String& str);
void getData();

void setup() {
  Serial.begin(115200);
  initDisplay();
  
  connectToWiFi();
  addText("Connecting to wifi");
  
  while (!isWiFiConnected())
  {
    addText(".");
    delay(500);
  }
  showMessage("");
  showMessage(getIPv4().c_str());
  initGrid(2);
  delay(500);


  addText("Loading data");
  getData();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdate >= 5000) {
    lastUpdate = currentMillis;
    getData();
  }
}

String getFirstWord(const String& str) {
  int spaceIndex = str.indexOf(' ');
  return (spaceIndex == -1) ? str : str.substring(0, spaceIndex);
}

void getData() {
  String json = getHardwareData(OHM_SERVER, OHM_PORT);
  Temps temps = parseHardwareData(json.c_str());

  showRow(getFirstWord(temps.cpuName).c_str(), temps.cpuTemp.c_str(), 0);
  showRow(getFirstWord(temps.gpuName).c_str(), temps.gpuTemp.c_str(), 1);
}