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
  display.setRotation(2);
  display.display();
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Display Ready");
  display.display();

}

void clearDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
}

void showMessage(const char* message) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

void showTemp(const char* temp)
{
  display.fillRect(0, 27, 128, 37, BLACK);

  display.setTextColor(WHITE);
  display.setTextSize(5);
  display.setFont(NULL);
  display.setCursor(6, 27);
  display.println(temp);
  display.display();
}

void showTitle(const char* title) {
  display.fillRect(0, 0, 128, 27, BLACK);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setFont(NULL);
  display.setCursor(0, 0);
  display.println(title);
  display.display();
}
