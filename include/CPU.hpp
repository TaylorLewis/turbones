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

    // Returns value at address in the program counter (PC), then increments the PC.
    uint8_t fetch();
    // Returns 16-bit value, concatenated (in little endian order)
    // from 8-bit values located at addresses PC+1 and PC.
    uint16_t fetch16();
    // Push value on the stack and decrement stack pointer.
    void push(const uint8_t& value);
    // Increment stack pointer and pop value from the stack.
    uint8_t pop();

    // Returns 16-bit value, concatenated (in little endian order)
    // from 8-bit values located at address+1 and address.
    uint16_t read16(const uint16_t& address);
    // Splits 16-bit value into two 8-bit values and push them to stack.
    void push16(const uint16_t& value);
    // Pops two 8-bit values and returns them concatenated as a 16-bit value.
    uint16_t pop16();

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



    // Addressing Modes
    void implied(void (CPU::*instruction)()) {
        (this->*instruction)();
    }
    void accumulator(void (CPU::*instruction)()) { // Special type of 'implied'. May be unnecessary.
        (this->*instruction)();
    }
    void immediate(void (CPU::*instruction)(const uint8_t)) {
        const uint8_t value = fetch();
        (this->*instruction)(value);
    }
    void zeroPage(void (CPU::*instruction)(const uint8_t)) {
        const uint8_t address = fetch();
        (this->*instruction)(address);
    }
    void zeroPageX(void (CPU::*instruction)(const uint8_t)) {
        const uint8_t address = fetch() + r_x;
        (this->*instruction)(address);
    }
    void zeroPageY(void (CPU::*instruction)(const uint8_t)) {
        const uint8_t address = fetch() + r_y;
        (this->*instruction)(address);
    }
    void relative(void (CPU::*instruction)(const int8_t)) {
        int8_t offset = (int8_t)fetch();
        (this->*instruction)(offset);
    }
    void absolute(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16();
        (this->*instruction)(address);
    }
    void absoluteX(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16() + r_x;
        (this->*instruction)(address);
    }
    void absoluteY(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16() + r_y;
        (this->*instruction)(address);
    }
    //void indirect(Instruction instruction);
    //void indexedIndirect(Instruction instruction);
    //void indirectIndexed(Instruction instruction);



    // Instructions
    void ADC(); // Add with Carry
    void AND(); // Logical AND
    void ASL(); // Arithmetic Shift Left
    void BCC(); // Branch if Carry Clear
    void BCS(); // Branch if Carry Set
    void BEQ(); // Branch if Equal
    void BIT(); // Bit Test
    void BMI(); // Branch if Minus
    void BNE(); // Branch if Not Equal
    void BPL(); // Branch if Positive
    void BRK(); // Force Interrupt
    void BVC(); // Branch if Overflow Clear
    void BVS(); // Branch if Overflow Set
    void CLC(); // Clear Carry Flag
    void CLD(); // Clear Decimal Mode
    void CLI(); // Clear Interrupt Disable
    void CLV(); // Clear Overflow Flag
    void CMP(); // Compare
    void CPX(); // Compare X Register
    void CPY(); // Compare Y Register
    void DEC(); // Decrement Memory
    void DEX(); // Decrement X Register
    void DEY(); // Decrement Y Register
    void EOR(); // Exclusive OR
    void INC(); // Increment Memory
    void INX(); // Increment X Register
    void INY(); // Increment Y Register
    void JMP(); // Jump
    void JSR(); // Jump to Subroutine
    void LDA(); // Load Accumulator
    void LDX(); // Load X Register
    void LDY(); // Load Y Register
    void LSR(); // Logical Shift Right
    void NOP(); // No Operation
    void ORA(); // Logical Inclusive OR
    void PHA(); // Push Accumulator
    void PHP(); // Push Processor Status
    void PLA(); // Pull Accumulator
    void PLP(); // Pull Processor Status
    void ROL(); // Rotate Left
    void ROR(); // Rotate Right
    void RTI(); // Return from Interrupt
    void RTS(); // Return from Subroutine
    void SBC(); // Subtract with Carry
    void SEC(); // Set Carry Flag
    void SED(); // Set Decimal Flag
    void SEI(); // Set Interrupt Disable
    void STA(); // Store Accumulator
    void STX(); // Store X Register
    void STY(); // Store Y Register
    void TAX(); // Transfer Accumulator to X
    void TAY(); // Transfer Accumulator to Y
    void TSX(); // Transfer Stack Pointer to X
    void TXA(); // Transfer X to Accumulator
    void TXS(); // Transfer X to Stack Pointer
    void TYA(); // Transfer Y to Accumulator
};