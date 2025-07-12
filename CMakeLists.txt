cmake_minimum_required(VERSION 3.28)
project(chip8-emulator)


add_executable(${PROJECT_NAME} src/main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} chip8 ${SDL2_LIBRARIES})
add_subdirectory(src)