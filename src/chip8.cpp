#include "chip8.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
/*
const Chip8::IN_EXEC Chip8::execute_modes[0xF] = {
   &Chip8::execute1, 
   &Chip8::execute2, 
   &Chip8::execute3, 
   &Chip8::execute4, 
   &Chip8::execute5, 
   &Chip8::execute6, 
   &Chip8::execute7, 
   &Chip8::execute8, 
   &Chip8::execute9, 
   &Chip8::executeA, 
   &Chip8::executeB, 
   &Chip8::executeC, 
   &Chip8::executeD, 
   &Chip8::executeE, 
   &Chip8::executeF, 
};
*/

Chip8::Chip8() {
   init();
}

int Chip8::run(int argc, char**argv) {
    if (argc < 2) {
        std::cout << "Usage: emu <rom_file>\n";
        return -1;
    }
    if (0 != load_rom(argv[1])) {
       std::cout << "Cannot load rom file\n"; 
       return -1;
    }
    while(true) {
        print_debug();
        fetch();
        decode();
        display.draw();
        print_video_buffer();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}

int Chip8::load_rom(char* file_name){
    std::ifstream file(file_name, std::ios::binary | std::ios::ate); // open at end to get size
    if (file.is_open()) {
        std::streamsize romSize = file.tellg();
		file.seekg(0, std::ios::beg);
        if (romSize > 4096 - 0x200) {
            return 1;
        }
        file.read(reinterpret_cast<char*>(memory + 0x200), romSize);
		file.close();
    } else {
        return 1;
}
return 0;
}

void Chip8::init() {
    for (int i{FONT_START_ADDR}; i <= FONT_END_ADDR; i++) {
        memory[i] = fontset[i - FONT_START_ADDR];
    }
}

void Chip8::fetch() {
    uint8_t hi = memory[pc];
    uint8_t lo = memory[pc + 1];
    curr_instruction = lo | (hi << 8);
    pc +=2;
}

void Chip8::decode() {
    // define macro for this
    instruction_parts instr_parts = {
        static_cast<uint8_t>(curr_instruction >> 12),
        static_cast<uint8_t>((curr_instruction >> 8) & 0xF),
        static_cast<uint8_t>((curr_instruction >> 4) & 0xF),
        static_cast<uint8_t>((curr_instruction) & 0xF),
        static_cast<uint8_t>(curr_instruction & 0xFF),
        static_cast<uint16_t>(curr_instruction & 0xFFF)
    };
    switch (instr_parts.first_nibble) {
        case 0x0:
            break;
        case 0x1:
            execute1(instr_parts);
            break;
        case 0x2:
            execute2(instr_parts);
            break;
        case 0x3:
            execute3(instr_parts);
            break;
        case 0x4:
            execute4(instr_parts);
            break;
        case 0x5:
            execute5(instr_parts);
            break;
        case 0x6:
            execute6(instr_parts);
            break;
        case 0x7:
            execute7(instr_parts);
            break;
        case 0x8:
            execute8(instr_parts);
            break;
        case 0x9:
            execute9(instr_parts);
            break;
        case 0xA:
            executeA(instr_parts);
            break;
        case 0xB:
            executeB(instr_parts);
            break;
        case 0xC:
            executeC(instr_parts);
            break;
        case 0xD: {
            executeD(instr_parts);
            break;
        }
        case 0xE:
            executeE(instr_parts);
            break;
        case 0xF:
            executeF(instr_parts);
            break;
    }
}

void Chip8::executeD(instruction_parts instr_parts){
    int x_coord = variable_registers[instr_parts.x];
    int y_coord = variable_registers[instr_parts.y];
    std::cout << "x" << x_coord << "y" << y_coord << "\n";

    variable_registers[0xF] = 0;
    int n = instr_parts.n;

    for (int i{0}; i < n; ++i) {
        uint8_t sprite_byte = memory[index_register + i];
        for (int j{0}; j < 8; ++j) {
            uint8_t bit = (sprite_byte >> (7 - j)) & 1;
            if (1 == bit) {
                int px = (x_coord + j) % Display::DISPLAY_WIDTH;
                int py = (y_coord + i) % Display::DISPLAY_HEIGHT;
                bool pixel = display.display_arr[py][px];
                if (pixel) {
                    display.display_arr[py][px] = false;
                    variable_registers[0xF] = 1;
                } else {
                    display.display_arr[py][px] = true;
                }
            }
        }
    }
            //  std::this_thread::sleep_for(std::chrono::milliseconds(9000));
}

void Chip8::print_video_buffer() {
    for (int y = 0; y < Display::DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < Display::DISPLAY_WIDTH; ++x) {
            uint32_t pixel = display.display_arr[y][x];
            if (pixel == true) {
                std::cout << "#";  // white pixel
            } else {
                std::cout << " ";  // black pixel
            }
        }
        std::cout << "\n";
    }
}

void Chip8::execute1(instruction_parts instr_parts){
    pc = instr_parts.nnn;
}
void Chip8::execute2(instruction_parts instr_parts){
    stack[sp] =  pc;
    sp += 1;
    pc = instr_parts.nnn;
}
void Chip8::execute3(instruction_parts instr_parts){
    if (instr_parts.nn == variable_registers[instr_parts.x]) {
        pc += 2;
    }
}
void Chip8::execute4(instruction_parts instr_parts){
    if (instr_parts.nn != variable_registers[instr_parts.x]) {
        pc += 2;
    }
}
void Chip8::execute5(instruction_parts instr_parts){
    if (variable_registers[instr_parts.x] == variable_registers[instr_parts.y]) {
        pc +=2;
    }
}
void Chip8::execute6(instruction_parts instr_parts){
    variable_registers[instr_parts.x] = instr_parts.nn;
}
void Chip8::execute7(instruction_parts instr_parts){
    variable_registers[instr_parts.x] += instr_parts.nn;
}
void Chip8::execute8(instruction_parts instr_parts){
    variable_registers[instr_parts.x] = variable_registers[instr_parts.y];
}
void Chip8::execute9(instruction_parts instr_parts){}
void Chip8::executeA(instruction_parts instr_parts){
    index_register = instr_parts.nnn;
}
void Chip8::executeB(instruction_parts instr_parts){}
void Chip8::executeC(instruction_parts instr_parts){}
void Chip8::executeE(instruction_parts instr_parts){}
void Chip8::executeF(instruction_parts instr_parts){}


void Chip8::print_debug() const {
    std::cout << std::hex << std::uppercase;

    std::cout << "==== CHIP-8 DEBUG STATE ====\n";
    std::cout << "INSTR: 0x" 
              << std::setw(4) << std::setfill('0') << curr_instruction << "\n";

    for (int i = 0; i < 16; ++i) {
        std::cout << "V" << std::hex << i << ": "
                  << std::setw(2) << std::setfill('0') << static_cast<int>(variable_registers[i]) << "  ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }

    std::cout << " I: 0x"  << std::setw(4) << std::setfill('0') << index_register << "\n";
    std::cout << "PC: 0x" << std::setw(4) << std::setfill('0') << pc << "\n";
    std::cout << "============================\n";
}
//https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#chip-8-splash-screen