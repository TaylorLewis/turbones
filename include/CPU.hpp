#pragma once

#include <stdint.h>
#include <array>

// The NES CPU, the 2A03 (or 2A07 for PAL), is based on the 6502.
class CPU {
public:
    CPU();


private:
    // Tracks number of emulated cycles.
    int cycles;

    // Memory.
    //   $0000 -$07FF
    //    2 KB internal RAM.
    //     $0000-$00FF
    //      Zero page. Addressable with a single byte.
    //   $0800-$1FFF
    //    Mirrors (3) of RAM.
    //     $0800-$0FFF
    //      Mirror 1.
    //     $1000-$17FF
    //      Mirror 2.
    //     $1800-$1FFF
    //      Mirror 3.
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
    std::array<uint8_t, 0xFFFF> memory; // = 65536 = 64 KB.

    // The following are the registers - denoted with the 'r_' prefix.
    // Accumulator. Used for arithmethical and logical operations.
    uint8_t r_a;
    // Index registers. Used for indexed addressing.
    uint8_t r_x, // Can directly alter stack pointer, unlike 'r_y'.
            r_y;
    // Program Counter. Contains the memory address of the next instruction to be executed.
    uint16_t r_pc;
    // Stack Pointer.
    uint8_t r_sp;
    // Status register.
    // Each bit is a boolean flag. Enumerating the bits:
    // 76543210
    // NV BDIZC
    // (with 0 being the least significant bit)
    // 0: Carry flag.
    // 1: Zero flag. Set if the result of the last instruction was 0.
    // 2: Interrupt inhibit. Disables response to maskable Interrupt Requests (IRQs). Doesn't affect Non-Maskable Interrupts (NMIs)
    // 3: Decimal mode. Would enable BCD (Binary Coded Decimal) mode, but it's disabled on the 2A03.
    // 4: Break Command.
    // 5: (Unused)
    // 6: Overflow flag. 
    // 7: Negative flag. 
    uint8_t r_p;
};