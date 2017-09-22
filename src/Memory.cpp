#include <iostream>

#include "Memory.hpp"

Memory::Memory(Mapper0* mapper, PPU* ppu) {
    this->mapper = mapper;
    this->ppu = ppu;
}

uint8_t Memory::read(const uint16_t& address) {
    if        (address <  0x2000) {
        return ram[address % 0x800];
    } else if (address <  0x4000) {
        return ppu->readRegister(0x2000 + (address % 8));
    } else if (address == 0x4014) {
        ppu->readRegister(address);
    } else if (address == 0x4015) {
        // apu->readRegister(address);
    } else if (address == 0x4016) {
        // Controller 1
    } else if (address == 0x4017) {
        // Controller 2
    } else if (address >= 0x6000) {
        return mapper->read(address);
    } else {
        std::cerr << "Unhandled memory read at: " << std::hex << (int)address << std::endl;
    }
}

void Memory::write(const uint16_t& address, const uint8_t& value) {
    if        (address <  0x2000) {
        ram[address % 0x800] = value;
    } else if (address <  0x4000) {
        return ppu->writeRegister(0x2000 + (address % 8), value);
    } else if (address <= 0x4013) {
        // apu->writeRegister(address, value);
    } else if (address == 0x4014) {
        ppu->writeRegister(address, value);
    } else if (address == 0x4015) {
        // apu->writeRegister(address, value);
    } else if (address == 0x4016) {
        // Controllers
    } else if (address == 0x4017) {
        // apu->writeRegister(address, value);
    } else if (address >= 0x6000) {
        return mapper->write(address, value);
    } else {
        std::cerr << "Unhandled memory write at: " << std::hex << (int)address
            << "\nwith value: " << (int)value << std::endl;
    }
}