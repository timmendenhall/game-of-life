cmake_minimum_required(VERSION 3.15)

project(gameoflife)

set(CMAKE_CXX_STANDARD 14)

## Include the re-usable dream lib
add_subdirectory(dream)
add_subdirectory(game)
