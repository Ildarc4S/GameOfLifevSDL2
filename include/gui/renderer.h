#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <stdexcept>

#include "../core/game.h"

class Renderer {
  public:
    Renderer(int window_width, int window_height,
             int field_width, int field_heights,
             int cell_size);
    ~Renderer();

    void render(const Field& field, bool is_pause) const;
    void renderText(const std::string& text,
                    int x, int y, int padding,
                    SDL_Color color, SDL_Color bg_color) const;
    int getCellSize() const;
    int getOffsetX() const;
    int getOffsetY() const;

  private:
    TTF_Font* font_;
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
