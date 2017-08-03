#pragma once

#include <stdint.h>
#include <array>

// Picture Processing Unit.
// Generates video.
class PPU {
public:
    void powerOn();

    uint8_t readRegister(const uint16_t& address);
    void writeRegister(const uint16_t& address, const uint8_t& value);

private:
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


    // Object Attribute Memory
    std::array<uint8_t, 0xFF> OAM;

};