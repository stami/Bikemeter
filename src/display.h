#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// =============================================================================

void setupDisplay();
void splashScreen();

// =============================================================================

void setupDisplay() {
  // Initialize with the I2C addr 0x3D (for the 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  splashScreen();
}

void splashScreen() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("The\nBikemeter");
  display.display();
  delay(1000);
  display.clearDisplay();
}

#endif
