cmake_minimum_required(VERSION 3.20)
project(GameLibs)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
  core/game.cc
  ../include/core/game.h
)

set_property(TARGET ${PROJECT_NAME} PROPERTY "${CMAKE_BINARY_DIR}/bin")

