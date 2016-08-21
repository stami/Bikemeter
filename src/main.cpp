#include "Arduino.h"

#include "variables.h"
#include "display.h"
#include "timer.h"
#include "meter.h"

void setup() {
  Serial.begin(9600);

  setupDisplay();
  setupTimer();
  setupMeter();
}

void loop() {
  if (SECOND_PASSED) {
    SECOND_PASSED = false;
    updateMeter();
  }
}
