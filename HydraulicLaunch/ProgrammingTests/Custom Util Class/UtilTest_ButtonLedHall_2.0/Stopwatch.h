// Stopwatch.h
#ifndef STOPWATCH_H
#define STOPWATCH_H

class Stopwatch {
  public:
    Stopwatch();
    void restartStopwatch();
    unsigned long getTimeElapsed();
  private:
    unsigned long startTime;
};

#endif // STOPWATCH_H
