#include "../../include/common/timer.h"

Timer::Timer(int interval_ms)
  : interval_ms_(interval_ms),
    last_update_(SDL_GetTicks()) {}

bool Timer::check() const {
  return (SDL_GetTicks() - last_update_)
         > static_cast<Uint32>(interval_ms_);
}

void Timer::reset() {
  last_update_ = SDL_GetTicks();
}