#include <iostream>

#include "NES.hpp"

NES::NES() : memory(&mapper, &ppu), cpu(&memory) {

}

void NES::load(const std::string& rom_path) {
    cart = Cartridge(rom_path);
    mapper.load(&cart);
}

void NES::run() {
    cpu.powerOn();
    ppu.powerOn();

    // TODO

    for (int i = 0; i < 50; ++i) { // testing
        cpu.step();

        ppu.step();
        ppu.step();
        ppu.step();
    }
}