#include <iostream>
#include "Chip8.h"
#include "Chip8Interface.h"
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
	// Chip8Interface d = Chip8Interface();	
	Chip8 chip = Chip8();
	return chip.run(argc, argv);
	//timing_timer = 0
	// isntruction timer = 0 
	// while (true) {
		// if 16 second have passed, reset timer and increment tmier register and do whatver the timer needs to do
		// if 700 Hz has passed, then you can fetch and decode the instruction and reset it to 0 
		// chip.fetch();
	// }
}
