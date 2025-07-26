# Chip8 Emulator

A Chip8 emulator written in C++ with the SDL library
Although I've called this project a Chip8 emulator, the Chip8 isn't really a peice of hardware, but rather an interpreted programming language/virtual machine/intstruction set architecture created by RCA engineer Joe Weisbecker as a way to make programs and games for his computer. Therefore, it would make more sesense to call it a *Chip8 Interpreter*.

For info on the specifications and instructions of the Chip8, the following site contains some good documentation http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#1.0

Inside the `rom` folder of the directory, you can find some test ROMs that test out the functionality of the emulator along with some games you can run on the Chip8. Whenever you run the Chip8, you can choose which ROM file you want to load up.


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

For Windows, use WSL and follow the steps above

### MacOS

- Install a C++ compiler: `xcode-select --install`
- Install CMake: `brew install cmake`
- Install SDL: `brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf`
- Create the build file in the project's top level directory: `mkdir build`
- cd into the build directory: `cd build`
- run CMake: `cmake ..`
- compile and link the project: `make`
- run the executable with a ROM file of your choice: `./chip8-emulator ../roms/<rom-file>`


