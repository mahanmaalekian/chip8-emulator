#include "chip8.h"

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
    display = Display();
}

void Chip8::init() {
    for (int i{FONT_END_ADDR}; i <= FONT_END_ADDR; i++) {
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
        (curr_instruction >> 12),
        (curr_instruction >> 8) & 0xF,
        (curr_instruction >> 4) & 0xF,
        (curr_instruction) & 0xF,
        curr_instruction & 0xFF,
        curr_instruction & 0xFFF
    };

    switch (instr_parts.first_nibble) {
        case 0x0:
            break;
        case 0x1:
            pc = instr_parts.nnn;
        case 0x6:
            variable_registers[instr_parts.x] = instr_parts.nn;
            break;
        case 0x7:
            variable_registers[instr_parts.x] += instr_parts.nn;
            break;
        case 0xA:
            index_register = instr_parts.nnn;
        case 0xD: {
            int x_coord = variable_registers[instr_parts.x] % 64;
            int y_coord = variable_registers[instr_parts.y] % 32;
            variable_registers[0xF] = 0;
            int n = instr_parts.n;

            for (int i{0}; i < n; i++){
                if (y_coord + i > Display::DISPLAY_HEIGHT) {
                    break;
                }
                uint8_t sprite_byte = memory[index_register + i];
                for (int j{0}; j < 8; j++) {
                    if (x_coord + j > Display::DISPLAY_WIDTH){
                        break;
                    }
                    uint8_t bit = (sprite_byte >> (7 - j)) & 1;
                    if (bit) {
                        if (display.display_arr[x_coord + j][y_coord+i]) {
                            display.display_arr[x_coord + j][y_coord+i] = false;
                            display.draw(x_coord + j, y_coord + i, Display::BLACK);
                            variable_registers[0xF] = 1;
                        }
                        else {
                            display.display_arr[x_coord + j][y_coord+i] = true;
                            display.draw(x_coord + j, y_coord + i, Display::WHITE);
                        }
                    }
                }

            }
            

        }
        default:
            break;
    }

}