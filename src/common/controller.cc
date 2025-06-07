#include "../../include/common/controller.h"

Controller::Controller(GameOfLife& game, Render& render, int update_interval)
  : game_(game), render_(render), update_interval_(update_interval) {}
void Controller::run(){}


GameOfLife& game_;
Render& render;
int updateInterval_;
void handleEvents();
