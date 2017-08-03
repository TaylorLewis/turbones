#include <iostream>

#include "Memory.hpp"

Memory::Memory(Mapper0* map) {
    mapper = map;
}

uint8_t Memory::read(const uint16_t& address) {
    if          (address < 0x2000) {
        return ram[address % 0x800];
    //} else if (address < 0x4000) {
    //    return PPU.readRegister[0x2000 + (address % 8)];
    //} else if (address < 0x4018) {
    //    // APU / IO stuff
    } else if (address >= 0x6000) {
        return mapper->read(address);
    } else {
        std::cerr << "Unhandled memory read at: " << std::hex << (int)address << std::endl;
    }
}

void Memory::write(const uint16_t& address, const uint8_t& value) {
    if          (address < 0x2000) {
        ram[address % 0x800] = value;
    //} else if (address < 0x4000) {
    //    return PPU.writeRegister[0x2000 + (address % 8)];
    //} else if (address < 0x4018) {
    //    // APU / IO stuff
    } else if (address >= 0x6000) {
        return mapper->write(address, value);
    } else {
        std::cerr << "Unhandled memory write at: " << std::hex << (int)address
            << "\nwith value: " << (int)value << std::endl;
    }
}

//void Memory::setMapper(Mapper* map) {
//    this->mapper = map;
//    std::cout << "Memory::setMapper finish." << std::endl; //d
//
//    std::cout << "Memory::setMapper test: " << std::hex << mapper->read(0x6000) << std::endl; //d
//}

