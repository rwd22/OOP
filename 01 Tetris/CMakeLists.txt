
cmake_minimum_required(VERSION 3.4)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(SFML COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_executable(tetris main.cpp tetro.cpp tetro.hpp)
target_link_libraries(tetris ${SFML_LIBRARIES})
