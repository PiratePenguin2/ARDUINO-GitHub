class Stopwatch {
  public:
    Stopwatch();
    void restartStopwatch();
    unsigned long getTimeElapsed();
  private:
    unsigned long startTime;
  };
