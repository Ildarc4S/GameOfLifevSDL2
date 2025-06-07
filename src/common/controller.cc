#include "../../include/common/controller.h"
#include <iostream>

void pring(const Field& f) {
  for(int i = 0; i < f.size(); ++i) {
    for(int j = 0; j < f[i].size(); ++j) {
      std::cout << f[i][j] << " ";
    }
  }
  std::cout << std::endl;
}

Controller::Controller(GameOfLife& game, Renderer& renderer, int update_interval)
  : game_(game), renderer_(renderer), update_interval_(update_interval) {}
void Controller::run() {
  while (game_.getState() != State::kExiting) {
    // std::cout << "State: " << static_cast<int>(game_.getState()) << std::endl;
    // pring(game_.getField());
    handleEvents();
    renderer_.render(game_.getField());
  }
}



void Controller::handleEvents() {
  SDL_Event event;
  auto empty_coords = std::make_pair(0, 0);
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        game_.update(Action::kExit, empty_coords);
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) {
          game_.update(Action::kTogglePause, empty_coords);
        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
          game_.update(Action::kExit, empty_coords);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT
            && game_.getState() == State::kPaused) {
          std::cout << "AA\n";
          int cellSize = renderer_.getCellSize();
          if (cellSize <= 0) {
            return;
          }
          int offset_x = renderer_.getOffsetX();
          int offset_y = renderer_.getOffsetY();
          int x = (event.button.x - offset_x) / cellSize;
          int y = (event.button.y - offset_y) / cellSize;
          game_.update(Action::kToogleCell, {x, y});
          std::cout << x << ":" << y << std::endl;
        }
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
