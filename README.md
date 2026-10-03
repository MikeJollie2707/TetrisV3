# SFML Tetris (version 3.0)

Previous versions are not well-coded for extensive uses, so this version attempts to fix that.

## Demo

![demo](demo.gif)

## Dependencies

C++17 is required.

SFML 3.x is required (tested with 3.1). SFML itself requires some system libraries, which are detailed in its tutorial: [here](https://www.sfml-dev.org/tutorials/3.1/getting-started/cmake/#requirements), [here](https://www.sfml-dev.org/tutorials/3.1/getting-started/linux/#installing-sfml), and [here (Windows)](https://www.sfml-dev.org/tutorials/3.1/getting-started/visual-studio/).

For Debian/Ubuntu, these are dependencies:

```sh
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev
```

From personal experience, you also need `libmbedtls-dev`, `libssh2-1-dev`, and `libharfbuzz-dev`.

## Run

```sh
cmake -B build
cmake --build build
```

Alternatively, if you use CMakeTools extension in VSCode, you can use it to build.

## Controls

- P: pause/unpause
- C: hold piece
- A/D: move left/right
- Space: fast drop
- ArrowLeft/ArrowRight: rotate left/right

The game starts out in a paused state. Press `P` to start.

## TODO

- [x] Music
