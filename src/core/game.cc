#include "../../include/core/game.h"

GameOfLife::GameOfLife(int width, int height)
  : width_(width), height_(height), state_(State::kPaused) {
  field_.resize(height, Row(width, false));
}

int GameOfLife::countNeighbors(int x, int y) const {
  int count = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue;
      int neighbour_x = x + i;
      int neighbour_y = y + j;
      if (neighbour_x >= 0 && neighbour_x < width_
          && neighbour_y >= 0 && neighbour_y < height_
          && field_[neighbour_x][neighbour_y]) {
        count++;
      }
    }
  }
  return count;
}

bool GameOfLife::checkRules(int x, int y) const {
  int neighbors_count = countNeighbors(y, x);
  return field_[y][x]
         ? (neighbors_count == 2 || neighbors_count == 3)
         : (neighbors_count == 3);
}

void GameOfLife::updateField() {
  Field new_field(height_, Row(width_, false));
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      new_field[i][j] = checkRules(j, i);
    }
  }
  field_ = std::move(new_field);
}

void GameOfLife::toogleCell(const Coords& coords) {
  const auto& [x, y] = coords;
  if (x >= 0 && x < width_
      && y >= 0 && y < height_) {
    field_[y][x] = !field_[y][x];
  }
}

void GameOfLife::update(const Action& action, const Coords& coords) {
  switch (state_) {
    case State::kPaused:
      switch (action) {
        case Action::kToogleCell:
          toogleCell(coords);
          break;
        case Action::kTogglePause:
          state_ = State::kRunning;
          break;
        case Action::kExit:
          state_ = State::kExiting;
          break;
        default:
          break;
      }
      break;
    case State::kRunning:
    switch (action) {
      case Action::kTogglePause:
        state_ = State::kPaused;
        break;
      case Action::kExit:
        state_ = State::kExiting;
        break;
      default:
        break;
    };
    case State::kExiting:
      break;
  };
}

void GameOfLife::clear() {
    for (auto& row : field_) {
        std::fill(row.begin(), row.end(), false);
    }
}

const Field& GameOfLife::getField() {
  if (state_ != State::kPaused) {
    updateField();
  }
  return field_;
}

int GameOfLife::getWidth() const {
  return width_;
}

int GameOfLife::getHeight() const {
  return height_;
}

State GameOfLife::getState() const {
  return state_;
}
