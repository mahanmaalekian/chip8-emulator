# Chip8 Emulator

A Chip8 emulator written in C++ using the SDL library.

Although this project is called a Chip8 emulator, the Chip8 is not actually a piece of hardware, but rather an interpreted programming language, virtual machine, and instruction set architecture created by RCA engineer Joe Weisbecker as a way to make programs and games for his computer. Therefore, it might be more accurate to call this project a *Chip8 interpreter*.

For information on the specifications and instructions of the Chip8, see the documentation [here](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#1.0).

Inside the `rom` folder of this directory, you can find some test ROMs that verify the functionality of the emulator, along with some game ROMs you can run. When you run the Chip8, you can choose which ROM file to load.


## Running the project

### Ubuntu/Debian/WSL

- Install a C++ compiler: `sudo apt install build-essential`
- Install CMake: `sudo apt install cmake`
- Install SDL: `sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev`
- Create the build file in the project's top level directory: `mkdir build`
- cd into the build directory: `cd build`
- run CMake: `cmake ..`
- compile and link the project: `make`
- run the executable with a ROM file of your choice: `./chip8-emulator ../roms/<rom-file>`

### Windows

For Windows, I highly recommend you use WSL and follow the steps above

### MacOS

- Install a C++ compiler: `xcode-select --install`
- Install CMake: `brew install cmake`
- Install SDL: `brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf`
- Create the build file in the project's top level directory: `mkdir build`
- cd into the build directory: `cd build`
- run CMake: `cmake ..`
- compile and link the project: `make`
- run the executable with a ROM file of your choice: `./chip8-emulator ../roms/<rom-file>`


