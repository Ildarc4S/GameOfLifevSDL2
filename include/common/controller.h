#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../core/game.h"
#include "../gui/renderer.h"

class Controller {
  public:
    Controller(GameOfLife& game, Renderer& renderer, int update_interval);
    void run();

  private:
    GameOfLife& game_;
    Renderer& renderer_;
    int update_interval_;
    void handleEvents();
};

#endif  // CONTROLLER_H