#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "variables.h"
#include "display.h"

// =============================================================================

void setupTimer();
void displayTime(unsigned long);
void printLeftPad(int);

// =============================================================================

ISR(TIMER1_COMPA_vect) {
  SECOND_PASSED = true;
}

// Setup Timer1 interrupts to happen between 1000 ms
void setupTimer() {
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 15624;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  // enable global interrupts:
  sei();
}

void displayTime(unsigned long millis) {
  display.setCursor(0, 50);
  display.setTextSize(2);

  unsigned long over;

  int hours = millis / 3600000;
  over = millis % 3600000;
  int minutes = over / 60000;
  over = over % 60000;
  int seconds = over / 1000;
  if (hours > 0) {
    printLeftPad(hours);
    display.print(":");
  }
  printLeftPad(minutes);
  display.print(":");
  printLeftPad(seconds);
}

void printLeftPad(int number){
  if (number < 10) {
    display.print("0");
  }
  display.print(number);
}

#endif
