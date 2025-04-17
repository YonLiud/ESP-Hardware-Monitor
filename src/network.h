#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>

void connectToWiFi();
bool isWiFiConnected();
void checkWiFi();
bool isServerReachable(const char* host, uint16_t port);
String getIPv4();
String getIPv6();
String getHardwareInfo(String ip, String port);


#endif