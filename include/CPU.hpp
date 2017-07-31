#pragma once

#include <stdint.h>
#include <array>
#include <memory>
#include <functional>

#include <Memory.hpp>

// The NES CPU, the 2A03 (or 2A07 for PAL), is based on the 6502.
class CPU {
public:
    CPU(Memory* mem);

    // Execute next instruction.
    void step();

private:
    void execute(const uint8_t& opcode);
    void push(uint8_t& value);
    uint8_t pop();

    Memory* memory;

    // Tracks number of emulated cycles.
    int cycles;

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
    // NV-BDIZC
    // (with 0 being the least significant bit)
    // 0: Carry flag.
    // 1: Zero flag. Set if the result of the last instruction was 0.
    // 2: Interrupt inhibit. Disables response to maskable Interrupt Requests (IRQs). Doesn't affect Non-Maskable Interrupts (NMIs)
    // 3: Decimal mode. Would enable BCD (Binary Coded Decimal) mode, but it's disabled on the 2A03.
    // 4: Break Command.
    // 5: (Unused)
    // 6: Overflow flag. 
    // 7: Negative flag. Set if the result of the last operation was negative.
    // TODO: Add interface to status flags
    uint8_t r_p;

    typedef void (CPU::*Instruction0)();        // Function taking 0 arguments.
    typedef void (CPU::*Instruction1)(uint8_t); // Function taking 1 argument.

    // Addressing Modes 
    void implied(Instruction0 instruction) { // Accumulator
        (this->*instruction)();
        ++r_pc;
    }
    void accumulator(Instruction1 instruction) { // Accumulator
        (this->*instruction)(r_a);
        ++r_pc;
    }
    //void immediate(Instruction instruction);       // Immediate
    //void zeroPage(Instruction instruction);        // Zero Page
    //void zeroPageX(Instruction instruction);       // Zero Page, X
    //void zeroPageY(Instruction instruction);       // Zero Page, Y
    //void relative(Instruction instruction);        // Relative
    //void absolute(Instruction instruction);        // Absolute
    //void absoluteX(Instruction instruction);       // Absolute, X
    //void absoluteY(Instruction instruction);       // Absolute, Y
    //void indirect(Instruction instruction);        // Indirect
    //void indexedIndirect(Instruction instruction); // Indexed Indirect
    //void indirectIndexed(Instruction instruction); // Indirect Indexed
};