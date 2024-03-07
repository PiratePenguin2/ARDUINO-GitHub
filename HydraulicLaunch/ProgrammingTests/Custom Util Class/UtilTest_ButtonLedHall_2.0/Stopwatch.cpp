// PT_Util::Stopwatch implementation
PT_Util::Stopwatch::Stopwatch() : startTime(0) {}

void PT_Util::Stopwatch::restartStopwatch() {
  startTime = millis();
}

unsigned long PT_Util::Stopwatch::getTimeElapsed() {
  return millis() - startTime;
}
