#include "chip8.h"

Chip8::Chip8() {
    init();
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
    uint8_t first_nibble = (curr_instruction >> 12);
    uint8_t second_nibble = (curr_instruction >> 8) & 0xF;
    uint8_t third_nibble = (curr_instruction >> 4) & 0xF;
    uint8_t fourth_nibble = (curr_instruction) & 0xF;
    uint8_t second_byte = curr_instruction & 0xFF;
    uint16_t nibble_234 = curr_instruction & 0xFFF;

    switch (first_nibble)
    {
    case 0x0:
        break;
    case 0x1:
        pc = nibble_234;
    case 0x6:
        variable_registers[second_nibble] = second_byte;
        break;
    case 0x7:
        variable_registers[second_nibble] += second_byte;
        break;
    case 0xA:
        index_register = nibble_234;
    default:
        break;
    }

}