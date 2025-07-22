add_library(chip8 Chip8.cpp Chip8Interface.cpp)

target_include_directories(chip8
	PUBLIC
	${CMAKE_SOURCE_DIR}/include)
