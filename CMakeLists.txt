cmake_minimum_required(VERSION 3.28)
project(TetrisV3 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 3.1 COMPONENTS Graphics Audio)
if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

add_subdirectory(src)
add_executable(tetris src/main.cpp)
target_compile_features(tetris PRIVATE cxx_std_17)
target_link_libraries(tetris PRIVATE tetris_lib)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tetris)