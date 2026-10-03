cmake_minimum_required(VERSION 3.28)
add_library(tetris_lib
    tetris.cpp
    tetromino.cpp
    
)
target_link_libraries(tetris_lib SFML::Graphics SFML::Audio)
target_include_directories(tetris_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)