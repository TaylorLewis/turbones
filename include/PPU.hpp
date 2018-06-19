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

    // $2007: PPUDATA
    // VRAM read/write data register.
    // After access, the video memory address will increment by an amount determined by 'ppuctrl_increment'.
    void writeData(const uint8_t& value);

    // Registers
    // TODO?: Change appropriate values to bools?
    //uint8_t controller;  // $2000: PPUCTRL
    //uint8_t mask;        // $2001: PPUMASK
    //uint8_t status;      // $2002: PPUSTATUS
    uint8_t oam_address; // $2003: OAMADDR
    uint8_t oam_data;    // $2004: OAMDATA
    uint8_t scroll;      // $2005: PPUSCROLL
    uint8_t address;     // $2006: PPUADDR
    uint8_t data;        // $2007: PPUDATA
    uint8_t oam_dma;     // $4014: OAMDMA

    // $2000: PPUCTRL: Controller
    uint8_t ppuctrl_nametable;        // Base nametable address (2 bit) (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
    uint8_t ppuctrl_increment;        // VRAM address increment per CPU read/write of PPUDATA (0: add 1, going across; 1: add 32, going down)
    uint8_t ppuctrl_sprite_table;     // Sprite pattern table address for 8x8 sprites (0: $0000; 1: $1000; ignored in 8x16 mode)
    uint8_t ppuctrl_background_table; // Background pattern table address (0: $0000; 1: $1000)
    uint8_t ppuctrl_sprite_size;      // (0: 8x8; 1: 8x16)
    uint8_t ppuctrl_master_slave;     // PPU master/slave select (0: read backdrop from EXT pins; 1: output color on EXT pins)
    uint8_t ppuctrl_nmi;              // Generate an NMI at the start of the vertical blanking interval (0: off; 1: on)

    // $2001: PPUMASK: Mask
    uint8_t ppumask_greyscale;            // (1: greyscale; 0: color)
    uint8_t ppumask_show_left_background; // (1: Show background in leftmost 8 pixels of screen; 0: Hide)
    uint8_t ppumask_show_left_sprites;    // (1: Show sprites in leftmost 8 pixels of screen; 0: Hide)
    uint8_t ppumask_show_background;
    uint8_t ppumask_show_sprites;
    uint8_t ppumask_tint_red;
    uint8_t ppumask_tint_green;
    uint8_t ppumask_tint_blue;

    // $2002 PPUSTATUS: Status
    // Sprite overflow.The intent was for this flag to be set
    // whenever more than eight sprites appear on a scanline, but a
    // hardware bug causes the actual behavior to be more complicated
    // and generate false positives as well as false negatives;
    // see PPU sprite evaluation. This flag is set during sprite
    // evaluation and cleared at dot 1 (the second dot) of the pre-render line.
    uint8_t ppustatus_sprite_overflow;
    // Sprite 0 Hit. Set when a nonzero pixel of sprite 0 overlaps a nonzero background pixel;
    // cleared at dot 1 of the pre-render line.  Used for raster timing.
    uint8_t ppustatus_sprite_zero_hit;
    // Vertical blank has started (0: not in vblank; 1: in vblank).
    // Set at dot 1 of line 241 (the line *after* the post-render line);
    // cleared after reading $2002 and at dot 1 of the pre-render line.
    uint8_t ppustatus_vblank;


    uint16_t vram_address;      // Current vram address.                                           (15 bit)
    uint16_t vram_address_temp; // Temporary vram address. (address of the top left onscreen tile) (15 bit)
    uint8_t  fine_x_scroll;     //                                                                  (3 bit)
    bool     write_flag;        // (0: 1st write; 1: 2nd write)                                     (1 bit)
    bool     odd_frame;        // (0: even frame; 1: odd frame)                                    (1 bit)

    // Each frame, 262 scanlines are rendered, each lasting 341 cycles.
    int scanline; // 0-261
    int cycle;    // 0-340


    // Object Attribute Memory, aka Sprite RAM.
    std::array<uint8_t, 0xFF> oam;

    std::array<uint8_t, 0x3FFF> vram;
};