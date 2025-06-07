#include "../../include/common/controller.h"
#include <iostream>

Controller::Controller(GameOfLife& game, Renderer& renderer, int update_interval)
  : game_(game), renderer_(renderer), update_interval_(update_interval) {}
void Controller::run() {
  while (game_.getState() != State::kExiting) {
    std::cout << "State: " << static_cast<int>(game_.getState()) << std::endl;
    renderer_.render(game_.getField());
  }
}

void Controller::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        game_.update(Action::kExit, std::make_pair(0, 0));
        break;

      default:
        break;
    };
  }
}

// GameOfLife& game_;
// Render& render;
// int updateInterval_;
// void handleEvents();
