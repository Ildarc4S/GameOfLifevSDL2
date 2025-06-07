#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>

#include "../core/game.h"

class Renderer {
  public:
    Renderer(int width, int height, int cell_size);
    ~Renderer();

    void render(const Field& field) const;
    SDL_Window* getWindow() const;

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int width_;
    int height_;
    int cell_size_;
};

#endif  // RENDERER_H