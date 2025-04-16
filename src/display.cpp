#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 16
#define SCK_PIN 15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay() {
  Wire.begin(SDA_PIN, SCK_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Display Ready");
  display.display();
}

void showMessage(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
