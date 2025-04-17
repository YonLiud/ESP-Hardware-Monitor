#include "display.h"
#include "network.h"
#include "hardware.h"
#include "config.h"
#include "data.h"

const String OHM_SERVER = "192.168.1.119";
const String OHM_PORT = "8085";

void setup() {
  Serial.begin(115200);
  initDisplay();
  showMessage("Starting...");
  connectToWiFi();
  String message = "IPv4: " + getIPv4();
  showMessage(message.c_str());

  delay(5000);
  showMessage("Loading Hardware Data...");
  delay(2000);
}

void loop() {
  String json = getHardwareData(OHM_SERVER, OHM_PORT);
  auto temps = parseHardwareData(json);
  
  Serial.print("CPU Temp: "); 
  Serial.println(temps.first); 
  
  Serial.print("GPU Temp: "); 
  Serial.println(temps.second);
  
  delay(3500);
}