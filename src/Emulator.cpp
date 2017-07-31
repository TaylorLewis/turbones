#include "Emulator.hpp"

void Emulator::run() {
    nes.load(rom_path);
    nes.run();
}



