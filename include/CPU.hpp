#pragma once

#include <stdint.h>
#include <array>
#include <bitset>

#include <Memory.hpp>

// The NES CPU, the 2A03 (or 2A07 for PAL), is based on the 6502.
class CPU {
public:
    CPU(Memory* mem);

    // Initialize registers to their power on state.
    void powerOn();
    // Handle any interrupt and execute next opcode.
    void step();

private:
    // Positions of status register flags. See status register comments.
    static constexpr int CARRY_FLAG = 0,
                         ZERO_FLAG = 1,
                         INTERRUPT_DISABLE = 2,
                         DECIMAL_MODE = 3,
                         BREAK_MODE_FLAG = 4,
                         UNUSED_BIT = 5,
                         OVERFLOW_FLAG = 6,
                         NEGATIVE_FLAG = 7;

    // Execute opcode instruction.
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

    void setZeroFlag(const uint8_t& value);
    void setNegativeFlag(const uint8_t& value);

    Memory* memory;

    // Tracks number of emulated cycles.
    int cycles;

    // Accumulator. Used for arithmethical and logical operations.
    uint8_t r_a;
    // Index registers. Used for indexed addressing.
    uint8_t r_x, // Can directly alter stack pointer, unlike register Y.
            r_y;
    // Program Counter. Contains the memory address of the next instruction to be executed.
    uint16_t pc;
    // Stack Pointer. Points to the next empty location on the stack. Counts downward.
    uint8_t sp;
    // Status register. Each bit is a boolean flag. 
    // Enumerating the bits (0 being the least significant):
    // 7654 3210
    // NV-B DIZC
    // 0: Carry Flag. 1 if last addition or shift resulted in a carry,
    //    or if last subtraction resulted in no borrow.
    // 1: Zero Flag. Set if the result of the last instruction was 0.
    // 2: Interrupt Disable. Disables response to maskable Interrupt Requests (IRQs).
    //    Doesn't affect Non-Maskable Interrupts (NMIs)
    // 3: Decimal Mode. Would enable BCD (Binary Coded Decimal) mode, but it's disabled on the 2A03.
    // 4: Break Command. Set when a BRK instruction has been executed and an interrupt has been generated to process it.
    // 5: Unused. Always set.
    // 6: Overflow Flag. Set when a signed arithmetic operation results in an invalid (overflowed) value. (e.g. 127+127 = -2).
    // 7: Negative Flag. Set if the result of the last operation had bit 7 (the leftmost) set to a one,
    //    denoting negativity in a signed binary number.
    std::bitset<8> r_p;



    // Addressing Modes. Gives an address to an instruction.
    // Many instructions have multiple opcodes, for each addressing mode they use.

    // Operand is an 8-bit constant value.
    void immediate(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = pc;
        ++pc;
        (this->*instruction)(address);
    }
    // Operand is an 8-bit address, addressing only the first 0x100 bytes of memory.
    void zeroPage(void (CPU::*instruction)(const uint8_t&)) {
        const uint8_t address = fetch();
        (this->*instruction)(address);
    }
    // Like Zero Page, but adds X register to the address.
    void zeroPageX(void (CPU::*instruction)(const uint8_t&)) {
        const uint8_t address = fetch() + r_x;
        (this->*instruction)(address);
    }
    // Like Zero Page, but adds Y register to the address.
    void zeroPageY(void (CPU::*instruction)(const uint8_t&)) {
        const uint8_t address = fetch() + r_y;
        (this->*instruction)(address);
    }
    // Corresponds to branch instructions. The (signed) 8-bit operand is an offset,
    // to be added to the PC if the condition is true, or ignored if false.
    void relative(void (CPU::*instruction)(const int8_t&)) {
        int8_t offset = (int8_t)fetch();
        (this->*instruction)(offset);
    }
    // Operand is a full 16-bit address.
    void absolute(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16();
        (this->*instruction)(address);
    }
    // Like Absolute, but adds X register to the address.
    void absoluteX(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16() + r_x;
        (this->*instruction)(address);
    }
    // Like Absolute, but adds Y register to the address.
    void absoluteY(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t address = fetch16() + r_y;
        (this->*instruction)(address);
    }
    // Operand is a 16-bit address points to another address.
    void indirect(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t firstAddress = fetch16();
        const uint16_t secondAddress = read16(firstAddress);
        (this->*instruction)(secondAddress);
    }
    // Operand is an 8-bit address to which the X register is added,
    // pointing to another address.
    void indexedIndirect(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t firstAddress = fetch() + r_x;
        const uint16_t secondAddress = read16(firstAddress);
        (this->*instruction)(secondAddress);
    }
    // Operand is an 8-bit address pointing to another address,
    // (the latter) to which the Y register is added.
    void indirectIndexed(void (CPU::*instruction)(const uint16_t&)) {
        const uint16_t firstAddress = fetch();
        const uint16_t secondAddress = read16(firstAddress) + r_y;
        (this->*instruction)(secondAddress);
    }

    //// No operands. All the necessary information is in the opcode.
    //void implied(void (CPU::*instruction)()) {
    //    (this->*instruction)();
    //}
    //// Special type of Implied, operating directing on the accumulator register. May be unnecessary.
    //void accumulator(void (CPU::*instruction)()) {
    //    (this->*instruction)();
    //}



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
    void JSR(const uint16_t& address); // Jump to Subroutine
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