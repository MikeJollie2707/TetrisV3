cmake_minimum_required(VERSION 3.16)
project(
    Tetrisv3

)

add_executable(
    tetris
    src/main.cpp
    src/tetromino.cpp
    src/tetris.cpp
    src/tetrisAI.cpp
)

# Link SFML
set(SFML_DIR ../../../SFML/SFML-2.5.1/build)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(tetris
    sfml-graphics 
    sfml-audio
)

target_include_directories(tetris
    PUBLIC include
)