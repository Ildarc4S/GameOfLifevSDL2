#ifndef GAME_H
#define GAME_H

#include <vector>

using Row = std::vector<bool>;
using Field = std::vector<Row>;
using Coords = std::pair<int, int>;

enum class Action {
  kToogleCell,
  kTogglePause,
  kExit
};

enum class State {
  kPaused,
  kRunning,
  kExiting
};

class GameOfLife {
 public:
  GameOfLife(int width, int height);

  void clear();
  void updateField();

  void update(const Action& action, const Coords& coords);

  const Field& getField();
  int getWidth() const;
  int getHeight() const;
  State getState() const;

 private:
  int width_;
  int height_;
  Field field_;
  State state_;

  int countNeighbors(int x, int y) const;
  bool checkRules(int x, int y) const;
  void toogleCell(const Coords& coords);
};

#endif  // GAME_H