# Match 3

|Action|Linux|Windows|MacOS|
|-------|-----|-------|-----|
| build | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Linux/badge.svg) | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Windows/badge.svg) | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_MacOS/badge.svg)
| cppcheck | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Linux_cppcheck/badge.svg)| N/A | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_MacOS_cppcheck/badge.svg)
| test | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Linux_Test/badge.svg) |![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Windows_Test/badge.svg) | ![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_MacOS_Test/badge.svg)|

Game demo with SDL2, C++11 with functional programming

![demo gif](docs/demo.gif)

# Build Instructions

## Linux

### Prerequisites
1. `git clone https://github.com/yatima1460/Match3.git`
2. `sudo apt install build-essential cmake libsdl2-dev libsdl2-ttf-dev`

### Compile
3. `mkdir build && cd build && cmake ..`
4. `make -C build -j`

### Run 
4. `./build/Match3`

## Windows

### Visual C++ 32/64-bit
- Opening it in latest Visual Studio versions supporting CMake or VSCode should work
- All binaries necessary are in Vendor and the CMake file will load them instead of searching system-wide libraries

### MinGW 
Not supported yet

## MacOS

1. `brew install sdl2 sdl2_ttf`
2. `mkdir build && cd build && cmake ..`
3. `make -C build -j`

# TODO

- Falling animation tied to delta time
- Smooth swapping animation
- Smooth destroyed animation
- Remove ugly static structs like AssetManager and Settings
- ~Add pure compiler-specific keywords around~
- Some type of logging
- Sound
- ~Google Test~
- Clang build too
- MessageBoxes for code errors
- Load game data from json files and replace Settings.ini too?
- Android build?
- Add other backends like OpenGL, DirectX, Vulkan?
- Score?

# Credits

License doesn't apply to assets

- Diamond icon from here:
https://www.iconexperience.com/g_collection/icons/?icon=diamond

- Background image from here:
    https://kr.best-wallpaper.net/Abstract-geometric-blue-lines-bright_wallpapers.html
