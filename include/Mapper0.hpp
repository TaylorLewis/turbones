#pragma once

#include "Cartridge.hpp"

// NROM.
class Mapper0 {
public:
    void load(Cartridge* cartridge);

    uint8_t read(const uint16_t& address);
    void write(const uint16_t& address, const uint8_t& value);

private:
    Cartridge* cart;

    //std::vector<uint_t> chr_ram; // 0x2000

    int prg_mirrored;
    //bool uses_chr_ram;
};