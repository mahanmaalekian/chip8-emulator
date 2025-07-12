add_library(chip8 chip8.cpp display.cpp)

target_include_directories(chip8
	PUBLIC
	${CMAKE_SOURCE_DIR}/include)
