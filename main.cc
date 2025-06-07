#include "include/common/controller.h"
#include "include/gui/renderer.h"

int main() {
  GameOfLife game(100, 200);
  Renderer renderer(100, 200, 30);
  Controller c(game, renderer, 1);
  c.run();

  return 0;
}
