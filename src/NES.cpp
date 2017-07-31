#include <iostream>

#include "NES.hpp"

NES::NES() : memory(&mapper), cpu(&memory) {

}

void NES::load(const std::string& rom_path) {
    cart = Cartridge(rom_path);
    mapper.load(&cart);

    std::cout << "NES::load finished." << std::endl; //d
}

void NES::run() {
    std::cout << "NES::run() start." << std::endl;

    // TODO

    for (int i = 0; i < 5; ++i) { // testing
        cpu.step();
    }
}