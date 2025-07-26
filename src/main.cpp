#include <iostream>
#include "Chip8.h"
#include "Chip8Interface.h"
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
	Chip8 chip = Chip8();
	return chip.run(argc, argv);
}
