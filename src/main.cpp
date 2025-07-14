#include <iostream>
#include "chip8.h"
#include "display.h"
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
	// Display d = Display();	
	Chip8 chip = Chip8(); // Chip8 should have argc and argv
	chip.run(argc, argv);
	//timing_timer = 0
	// isntruction timer = 0 
	// while (true) {
		// if 16 second have passed, reset timer and increment tmier register and do whatver the timer needs to do
		// if 700 Hz has passed, then you can fetch and decode the instruction and reset it to 0 
		// chip.fetch();
	// }
std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}
