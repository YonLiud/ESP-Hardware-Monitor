#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"
#include "images.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 16
#define SCK_PIN 15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay(bool inverted) {
  Wire.begin(SDA_PIN, SCK_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  display.setRotation(2);
  display.invertDisplay(inverted);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  drawImage(epd_bitmap_POLARAS);
  display.display();

}

void clearDisplay()
{
  display.clearDisplay();
  display.setCursor(1, 1);
  display.display();
}

void showMessage(const char* message) {
  display.setTextSize(1);
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
  display.setCursor(2, 0);
  display.println(title);
  display.display();
}

void drawImage(const unsigned char* image) {
  display.clearDisplay();
  display.drawBitmap(0, 0, image, 128, 64, 1); // 1 = color (white)
  display.display();
}