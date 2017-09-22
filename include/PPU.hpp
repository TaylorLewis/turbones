#pragma once

#include <stdint.h>
#include <array>

// Picture Processing Unit.
// Generates video.
class PPU {
public:
    void powerOn();
    void step();

    uint8_t readRegister(const uint16_t& address);
    void writeRegister(const uint16_t& address, const uint8_t& value);

private:
    static constexpr int WIDTH  = 256,
                         HEIGHT = 240;

    // Registers
    uint8_t controller,  // $2000: PPUCTRL
            mask,        // $2001: PPUMASK
            status,      // $2002: PPUSTATUS
            oam_address, // $2003: OAMADDR
            oam_data,    // $2004: OAMDATA
            scroll,      // $2005: PPUSCROLL
            address,     // $2006: PPUADDR
            data,        // $2007: PPUDATA
            oam_dma;     // $4014: OAMDMA

    uint16_t vram_address;      // Current vram address.   (15 bit)
    uint16_t vram_address_temp; // Temporary vram address. (15 bit)
    uint8_t  x;                 // Fine x scroll            (3 bit)
    bool     w;                 // Write toggle             (1 bit)
    bool     f;                 // Even/odd frame flag      (1 bit)


    // Object Attribute Memory, aka Sprite RAM.
    std::array<uint8_t, 0xFF> oam;

    std::array<uint8_t, 0x3FFF> vram;
};