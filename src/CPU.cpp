#include <iostream>

#include "CPU.hpp"
#include "Opcodes.hpp"

CPU::CPU(Memory* mem) {
    memory = mem;

    r_a = 0;
    r_x = 0;
    r_y = 0;

    r_sp = 0xFD;

    r_p = 0b0011'0100;

    r_pc = 0x8000;
}

void CPU::step() {
    // TODO: Handle interrupts

    const uint8_t opcode = memory->read(r_pc);
    execute(opcode);
    
    cycles += cycle_table[opcode];
}

void CPU::execute(const uint8_t& opcode) {
    std::cout << "CPU::execute opcode: " << std::hex << (int)opcode << std::endl;  //d
    switch (opcode) {


        default:
            std::cerr << "Unsupported opcode: " << instruction_table[opcode] << std::endl;
    }
}

void CPU::push(uint8_t & value) {
    memory->write(0x100 + r_sp, value);
    --r_sp;
}

uint8_t CPU::pop() {
    ++r_sp;
    return memory->read(0x100 + r_sp);
}