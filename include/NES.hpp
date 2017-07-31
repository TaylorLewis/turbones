#pragma once

#include <string>

#include <Cartridge.hpp>
#include <Mapper0.hpp>
#include <Memory.hpp>
#include <CPU.hpp>
#include <PPU.hpp>
#include <APU.hpp>

class NES {
public:
    NES();
    void load(const std::string& rom_path);
    void run();

private:
    Memory memory;
    Mapper0 mapper; // TODO: Generalize

    CPU cpu;
    PPU ppu;
    APU apu;
    Cartridge cart;
};