#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../core/game.h"
#include "../gui/renderer.h"

class Controller {
  public:
    Controller(GameOfLife& game, Render& render, int update_interval);
    void run();

  private:
    GameOfLife& game_;
    Render& render_;
    int update_interval_;
    void handleEvents();
};

#endif  // CONTROLLER_H