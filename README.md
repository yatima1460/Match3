# Match 3

|Project|Linux|Windows|MacOS|
|-------|-----|-------|-----|
| Match3 | [![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Linux/badge.svg)](https://github.com/yatima1460/Match3/actions) | [![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Windows/badge.svg)](https://github.com/yatima1460/Match3/actions) | [![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_MacOS/badge.svg)](https://github.com/yatima1460/Match3/actions)|
| Match3 Test | [![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Test_Linux/badge.svg)](https://github.com/yatima1460/Match3/actions) |[![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Test_Windows/badge.svg)](https://github.com/yatima1460/Match3/actions) | [![Actions Status](https://github.com/yatima1460/Match3/workflows/Match3_Test_MacOS/badge.svg)](https://github.com/yatima1460/Match3/actions)|

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
4. `./build/Output/Match3`

## Windows

### Visual C++ 32/64-bit
- Opening it in latest Visual Studio versions supporting CMake or VSCode should work
- All binaries necessary are in Vendor and the CMake file will load them instead of searching system-wide libraries

### MinGW 
TODO

## MacOS
TODO


# Credits

License doesn't apply to assets

- Diamond icon from here:
https://www.iconexperience.com/g_collection/icons/?icon=diamond

- Background image from here:
    https://kr.best-wallpaper.net/Abstract-geometric-blue-lines-bright_wallpapers.html
