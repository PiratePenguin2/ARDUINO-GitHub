  // PT_Util::Timer implementation
PT_Util::Timer::Timer() {
}

PT_Util::Timer::Timer(int mSec) {
  setTimer(mSec);
}

void PT_Util::Timer::setTimer(int mSec) {
  duration = mSec;
  startTime = millis();
}

unsigned long PT_Util::Timer::getStartTime() {
  return startTime;
}

unsigned long PT_Util::Timer::getEndTime() {
  return startTime + duration;
}

unsigned long PT_Util::Timer::getElapsedTime() {
  unsigned long currentTime = millis();
  if (currentTime >= startTime) {
    return currentTime - startTime;
  } else {
    // Handle rollover
    return (4294967295UL - 1 - startTime) + currentTime + 1;
  }
}

unsigned long PT_Util::Timer::getTimeLeft() {
  unsigned long elapsedTime = getElapsedTime();
  if (elapsedTime >= duration) {
    return 0; // Timer finished
  } else {
    return duration - elapsedTime;
  }
}

bool PT_Util::Timer::timerFinished() {
  unsigned long currentTime = millis();
  if (currentTime >= startTime) {
    return (currentTime - startTime >= duration);
  } else {
    // Handle rollover
    return (4294967295UL - startTime + currentTime >= duration);
  }
}
