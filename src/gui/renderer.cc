#include "../../include/gui/renderer.h"

Renderer::Renderer(int window_width, int window_height,
                   int field_width, int field_heights,
                   int cell_size)
  : window_width_(window_width), window_height_(window_height),
    field_width_(field_width), field_height_(field_heights),
    cell_size_(cell_size) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
  }
  window_ = SDL_CreateWindow("Game of Life",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             window_width, window_height,
                             SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);

  offset_x_ = (window_width - field_width_ * cell_size) / 2;
  offset_y_ = (window_height - field_height_ * cell_size) / 2;

  if (SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255) < 0) {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
    throw std::runtime_error("SDL_SetRenderDrawColor failed: " + std::string(SDL_GetError()));
  }
  if (SDL_RenderClear(renderer_) < 0) {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
    throw std::runtime_error("SDL_RenderClear failed: " + std::string(SDL_GetError()));
  }
  SDL_RenderPresent(renderer_);

  if (TTF_Init() == -1) {
    throw std::runtime_error("TTF_Init failed: " + std::string(TTF_GetError()));
  }
  font_ = TTF_OpenFont("../assets/fonts/Roboto.ttf", 24);
  if (!font_) {
    throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Renderer::render(const Field& field, bool is_pause) const {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

  for (size_t y = 0; y < field.size(); ++y) {
    for (size_t x = 0; x < field[y].size(); ++x) {
      if (field[y][x]) {
        SDL_Rect rect = {
            offset_x_ + static_cast<int>(x * cell_size_),
            offset_y_ + static_cast<int>(y * cell_size_),
            cell_size_,
            cell_size_
        };
        if (SDL_RenderFillRect(renderer_, &rect) < 0) {
          return;
        }
      }
    }
  }

  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
for (int x = 0; x <= static_cast<int>(field[0].size()) * cell_size_; x += cell_size_) {
    if (SDL_RenderDrawLine(renderer_, offset_x_ + x, offset_y_,
                           offset_x_ + x, offset_y_ + static_cast<int>(field.size() * cell_size_)) < 0) {
      return;
    }
  }
  for (int y = 0; y <= static_cast<int>(field.size()) * cell_size_; y += cell_size_) {
    if (SDL_RenderDrawLine(renderer_, offset_x_, offset_y_ + y,
                           offset_x_ + static_cast<int>(field[0].size() * cell_size_),
                           offset_y_ + y) < 0) {
      return;
    }
  }


  std::string statusText = is_pause ? "Paused" : "Running";
  SDL_Color textColor = {0, 0, 0, 255};
  SDL_Color bgColor = {200, 200, 200, 128};
  int padding = 5;
  renderText(statusText, offset_x_, offset_y_, padding, textColor, bgColor);
  SDL_RenderPresent(renderer_);
}

void Renderer::renderText(const std::string& text,
                          int x, int y, int padding,
                          SDL_Color color, SDL_Color bg_color) const {
  int textWidth, textHeight;
  TTF_SizeText(font_, text.c_str(), &textWidth, &textHeight);

  SDL_Rect bgRect = {
    x - padding / 2,
    y - padding / 2,
    textWidth + padding,
    textHeight + padding
  };
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer_, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderFillRect(renderer_, &bgRect);

  SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
  if (!surface) {
      return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  if (!texture) {
      SDL_FreeSurface(surface);
      return;
  }

  SDL_Rect rect = {x, y, surface->w, surface->h};
  SDL_RenderCopy(renderer_, texture, nullptr, &rect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

int Renderer::getCellSize() const {
  return cell_size_;
}
int Renderer::getOffsetX() const {
  return offset_x_;
}
int Renderer::getOffsetY() const {
  return offset_y_;
}
