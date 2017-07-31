#include <iostream>

#include "Mapper0.hpp"

void Mapper0::load(Cartridge* cartridge) {
    this->cart = cartridge;

    prg_mirrored = !(cart->prg_rom.size() == Cartridge::PRG_PAGE_SIZE);
}

uint8_t Mapper0::read(const uint16_t& address) {
    if        (address < 0x6000) {
        std::cerr << "Mapper0 read out of bounds: " << std::hex << (int)address << std::endl;
    } else if (address < 0xC000) {
        return cart->prg_rom[address % 0x8000];
    } else { // (address >= 0xC000)
        if (prg_mirrored) {
            return cart->prg_rom[address % Cartridge::PRG_PAGE_SIZE]; }
        else {
            return cart->prg_rom[address % 0x8000]; }
    }
}

void Mapper0::write(const uint16_t& address, const uint8_t& value) {
    // TODO
    std::cerr << "Mapper0::write called." << std::endl;
}
