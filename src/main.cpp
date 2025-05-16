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

String getFirstWord(const String& str);

void setup() {
  Serial.begin(115200);
  initDisplay();
  
  // showConnectionScreen();
  // connectToWiFi();
  // ensureConnection();
  
  // if (isWiFiConnected()) {
  //   clearDisplay();
  //   showMessage(getIPv4().c_str());
  //   delay(3000);
  // }

  initGrid(2);

  showRow("AMD", "55", 0);
  showRow("NVIDIA", "85", 1);

}

void loop() {
  
}

String getFirstWord(const String& str) {
  int spaceIndex = str.indexOf(' ');
  return (spaceIndex == -1) ? str : str.substring(0, spaceIndex);
}