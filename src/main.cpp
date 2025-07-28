#include "Chip8.h"

int main(int argc, char **argv) {
	Chip8 chip = Chip8();
	return chip.run(argc, argv);
}
