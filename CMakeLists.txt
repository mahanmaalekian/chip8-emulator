cmake_minimum_required(VERSION 3.28)
project(chip8-emulator)


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} chip8)

add_subdirectory(src)

