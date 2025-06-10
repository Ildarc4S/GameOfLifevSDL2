cmake_minimum_required(VERSION 3.20)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

add_executable(${PROJECT_NAME}
  main.cc
  src/gui/renderer.cc
  src/common/controller.cc
  src/common/timer.cc

  include/gui/renderer.h
  include/common/controller.h
  include/common/timer.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC GameLibs ${SDL2_LIBRARIES} SDL2_ttf)

set_property(TARGET ${PROJECT_NAME} PROPERTY "${CMAKE_BINARY_DIR}/bin")

