#include "CPU.hpp"

CPU::CPU() {
    r_a = 0;
    r_x = 0;
    r_y = 0;

    r_sp = 0xFD;

    r_p = 0b00110100;

    // TODO: What is the PC set to?

    for (uint8_t &elem : memory) {
        elem = 0;
    }
}