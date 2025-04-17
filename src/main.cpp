#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"
#include "data.h"

const String OHM_SERVER = SERVER_URL;
const String OHM_PORT = "8085";

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
  showTitle("CPU & GPU");
}

void loop() {
  String json = getHardwareData(OHM_SERVER, OHM_PORT);
  auto temps = parseHardwareData(json.c_str());

  Serial.print("CPU Temp: "); 
  Serial.println(temps.first); 

  Serial.print("GPU Temp: "); 
  Serial.println(temps.second);

  showTemp(temps.first.c_str());

  delay(1000);
}
