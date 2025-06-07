#include <string>
#include <iostream>

#include "include/common/controller.h"
#include "include/gui/renderer.h"

struct GameConfig {
    int window_width = 1000;
    int window_height = 1000;
    int cell_size = 10;
    int update_interval = 100;
    bool help_mode = false;
};

GameConfig parseCommandLine(int argc, char** argv) {
  GameConfig config;
  bool has_width = false, has_height = false, has_cell_size = false, has_fps = false;

  for (int i = 1; i < argc && !config.help_mode; ++i) {
    std::string arg = argv[i];
    if (arg == "--help") {
      std::cout << "Usage: " << argv[0] << " -w <width> -h <height> -s <size> -f <fps>\n"
                << "Options (all required):\n"
                << "  -w <width>     Window width in pixels\n"
                << "  -h <height>    Window height in pixels\n"
                << "  -s <size>      Cell size in pixels\n"
                << "  -f <fps>       Update frequency in FPS\n"
                << "  --help         Show this help message\n";
      config.help_mode = true;
    } else {
      if ((arg == "-w" || arg == "-h" || arg == "-s" || arg == "-f") && i + 1 >= argc) {
        throw std::invalid_argument("Missing value for option: " + arg);
      }
      try {
        if (arg == "-w") {
          config.window_width = std::stoi(argv[++i]);
          if (config.window_width < 200) {
            throw std::invalid_argument("Window width should be more than 200");
          }
          has_width = true;
        }
        else if (arg == "-h") {
          config.window_height = std::stoi(argv[++i]);
          if (config.window_height < 200) {
            throw std::invalid_argument("Window height should be more than 200");
          }
          has_height = true;
        }
        else if (arg == "-s") {
          config.cell_size = std::stoi(argv[++i]);
          if (config.cell_size < 50) {
            throw std::invalid_argument("Cell size should be more than 50");
          } else if (config.cell_size > config.window_height
                     || config.cell_size > config.window_width) {
            throw std::invalid_argument("Cell size not correct");
          }
          has_cell_size = true;
        }
        else if (arg == "-f") {
          int fps = std::stoi(argv[++i]);
          if (fps <= 0) {
            throw std::invalid_argument("FPS must be positive");
          }
          config.update_interval = 1000 / fps;
          has_fps = true;
        }
        else {
          throw std::invalid_argument("Unknown option: " + arg);
        }
      } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid argument for " + arg + ": " + e.what());
      } catch (const std::out_of_range& e) {
        throw std::invalid_argument("Value out of range for " + arg);
      }
    }
  }
  if ((!has_width || !has_height || !has_cell_size || !has_fps) && !config.help_mode) {
      std::string missing;
      if (!has_width) missing += "-w ";
      if (!has_height) missing += "-h ";
      if (!has_cell_size) missing += "-s ";
      if (!has_fps) missing += "-f ";
      throw std::invalid_argument("Missing required options: " + missing);
  }

  return config;
}

int main(int argc, char** argv) {
  try {
    GameConfig game_config = parseCommandLine(argc, argv);
    if (!game_config.help_mode) {
      int field_width = game_config.window_width / game_config.cell_size;
      int field_height = game_config.window_height / game_config.cell_size;
      GameOfLife game(field_width, field_height);

      Renderer renderer(game_config.window_width, game_config.window_height, field_width, field_height, game_config.cell_size);
      Controller game_controller(game, renderer, game_config.update_interval);
      game_controller.run();
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
