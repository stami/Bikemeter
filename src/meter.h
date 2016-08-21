#ifndef METER_H
#define METER_H

#include "variables.h"
#include "display.h"
#include "timer.h"

// =============================================================================

void ISR_SPIN();
void setupMeter();
void displayDistance(double);
void displaySpeed(double);
void displayAvgSpeed(double);

// =============================================================================


// Called when magnet passes the reed switch
void ISR_SPIN() {
  SPIN_DETECTED = true;
  spins += 1;
}

// Setup Magnet interrupt
void setupMeter() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR_SPIN, FALLING);
}

// Called between 1 second
void updateMeter() {
  // Take spins from last second and allow registering new ones
  int pastSpins = spins;
  spins = 0;

  double lastDistance = pastSpins; // meters
  distance += lastDistance;

  unsigned long timeNow = millis();
  double speed = lastDistance * 3.6; // distance / 1s * 3.6 [km/h]
  double kilometers = distance / 1000;
  double avgSpeed = distance * 3.6; // km/h

  display.clearDisplay(); // Clear display buffer
  displaySpeed(speed);
  displayDistance(kilometers);
  displayAvgSpeed(avgSpeed);
  displayTime(timeNow);
  display.display(); // Display current buffer
}

void displaySpeed(double speed) {
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.print(speed, 1);
  display.setTextSize(1);
  display.print("km/h");
}

void displayDistance(double distance) {
  display.setCursor(70, 15);
  display.setTextSize(2);
  display.print(distance, 1);
  display.setTextSize(1);
  display.print("km");
}

void displayAvgSpeed(double avgSpeed) {
  display.setCursor(70, 50);
  display.setTextSize(2);
  display.print(avgSpeed, 1);
  display.setCursor(70, 40);
  display.setTextSize(1);
  display.println("Avg");
}

#endif
