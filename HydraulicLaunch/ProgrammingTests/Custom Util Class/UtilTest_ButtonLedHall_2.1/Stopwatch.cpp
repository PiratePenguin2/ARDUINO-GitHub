// PT_Util::Stopwatch implementation
#include <Arduino.h>
#include "Stopwatch.h"

Stopwatch::Stopwatch() : startTime(0) {}

void Stopwatch::restartStopwatch() {
  startTime = millis();
}

unsigned long Stopwatch::getTimeElapsed() {
  return millis() - startTime;
}
