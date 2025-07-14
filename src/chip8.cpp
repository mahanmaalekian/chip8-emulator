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
        fetch();
        decode();
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
    // for (int i{FONT_END_ADDR}; i <= FONT_END_ADDR; i++) {
    //     memory[i] = fontset[i - FONT_START_ADDR];
    // }
}

void Chip8::fetch() {
    uint8_t hi = memory[pc];
    uint8_t lo = memory[pc + 1];
    curr_instruction = lo | (hi << 8);
std::cout << "first instruction: 0x"
          << std::setw(4) << std::setfill('0') << std::hex
          << curr_instruction << std::dec << "\n";
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
            std::cout<<"0\n";
            break;
            
        case 0x1:
            pc = instr_parts.nnn;//
            std:: cout <<"1\n";
            break;
        case 0x6:
            variable_registers[instr_parts.x] = instr_parts.nn;
            std:: cout <<"6\n";
            break;
        case 0x7:
            variable_registers[instr_parts.x] += instr_parts.nn;
            std:: cout <<"7\n";
            break;
        case 0xA:
            index_register = instr_parts.nnn;
            std:: cout <<"a\n";
            break;
        case 0xD: {
            std::cout << "d\n";

int x_coord = variable_registers[instr_parts.x];
int y_coord = variable_registers[instr_parts.y];
std::cout << "x" << x_coord << "y" << y_coord << "\n";

variable_registers[0xF] = 0;
int n = instr_parts.n;

for (int i{0}; i < n; ++i) {
    uint8_t sprite_byte = memory[index_register + i];
    for (int j{0}; j < 8; ++j) {
        uint8_t bit = (sprite_byte >> (7 - j)) & 1;
        if (bit) {
            int px = (x_coord + j) % Display::DISPLAY_WIDTH;
            int py = (y_coord + i) % Display::DISPLAY_HEIGHT;

            if (display.display_arr[py][px]) {
                display.display_arr[py][px] = false;
                display.draw(px, py, Display::BLACK);
                variable_registers[0xF] = 1;
            } else {
                display.display_arr[py][px] = true;
                display.draw(px, py, Display::WHITE);
            }
        }
    }
}

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        break;
        }
        default:
            break;
    }

           std:: cout << "V0 "<< variable_registers[0] << " V1 " << std::hex<< variable_registers[1] << " I " <<  std::hex << index_register << "\n";
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
        std::cout << "\n";  // new line after each row
    }
}
