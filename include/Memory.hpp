#pragma once

#include <stdint.h>
#include <array>

#include <Mapper0.hpp>
#include <PPU.hpp>

// Memory.
//   $0000 -$07FF
//    2 KB internal RAM.
//     $0000-$00FF
//      Zero page. Addressable with a single byte.
//     $0100–$01FF
//      Stack memory.
//   $0800-$1FFF
//    Mirrors (3) of RAM.
//   $2000-$2007
//    PPU registers.
//   $2008-$3FFF
//    Mirrors (1023) of PPU registers.
//   $4000-$4017
//    APU and I/O registers
//   $4018-$401F
//    APU and I/O functionality that is normally disabled.
//   $4020-$FFFF
//    Cartridge space: PRG ROM, PRG RAM, and mapper registers. 
class Memory {
public:
    Memory(Mapper0* mapper, PPU* ppu);

    uint8_t read(const uint16_t& address);
    void write(const uint16_t& address, const uint8_t& value);

private:
    Mapper0* mapper;
    PPU* ppu;

    std::array<uint8_t, 0x800> ram;
};