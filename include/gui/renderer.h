#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>

#include "../core/game.h"

class Renderer {
  public:
    Renderer(int window_width, int window_height,
             int field_width, int field_heights,
             int cell_size);
    ~Renderer();

    void render(const Field& field) const;
    SDL_Window* getWindow() const;
    int getCellSize() const;
    int getOffsetX() const;
    int getOffsetY() const;

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int window_width_;
    int window_height_;
    int field_width_;
    int field_height_;
    int cell_size_;
    int offset_x_;
    int offset_y_;
};

#endif  // RENDERER_H