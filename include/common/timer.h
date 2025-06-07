#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer {
 public:
  explicit Timer(int interval_ms);
  bool check() const;
  void reset();

 private:
  int interval_ms_;
  Uint32 last_update_;
};

#endif  // TIMER_H