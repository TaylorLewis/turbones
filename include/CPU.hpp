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
    uint16_t immediate() {
        const uint16_t address = pc;
        ++pc;
        return address;
    }
    // Operand is an 8-bit address, addressing only the first 0x100 bytes of memory.
    uint16_t zeroPage() {
        const uint16_t address = fetch();
        return address;
    }
    // Like Zero Page, but adds X register to the address.
    uint16_t zeroPageX() {
        const uint16_t address = fetch() + r_x;
        return address;
    }
    // Like Zero Page, but adds Y register to the address.
    uint16_t zeroPageY() {
        const uint16_t address = fetch() + r_y;
        return address;
    }
    // Corresponds to branch instructions. The (signed) 8-bit operand is an offset,
    // to be added to the PC if the condition is true, or ignored if false.
    uint16_t relative() {
        const uint16_t address = pc;
        ++pc;
        return address;
    }
    // Operand is a full 16-bit address.
    uint16_t absolute() {
        const uint16_t address = fetch16();
        return address;
    }
    // Like Absolute, but adds X register to the address.
    uint16_t absoluteX() {
        const uint16_t address = fetch16() + r_x;
        return address;
    }
    // Like Absolute, but adds Y register to the address.
    uint16_t absoluteY() {
        const uint16_t address = fetch16() + r_y;
        return address;
    }
    // Operand is a 16-bit address points to another address.
    uint16_t indirect() {
        const uint16_t firstAddress = fetch16();
        const uint16_t secondAddress = read16(firstAddress);
        return secondAddress;
    }
    // Operand is an 8-bit address to which the X register is added,
    // pointing to another address.
    uint16_t indexedIndirect() {
        const uint16_t firstAddress = fetch() + r_x;
        const uint16_t secondAddress = read16(firstAddress);
        return secondAddress;
    }
    // Operand is an 8-bit address pointing to another address,
    // (the latter) to which the Y register is added.
    uint16_t indirectIndexed() {
        const uint16_t firstAddress = fetch();
        const uint16_t secondAddress = read16(firstAddress) + r_y;
        return secondAddress;
    }

    //// No operands. All the necessary information is in the opcode.
    //void implied();
    //// Special type of Implied, operating directing on the accumulator register. May be unnecessary.
    //void accumulator();



    // Instructions
    void ADC(const uint16_t& address); // Add with Carry
    void AND(const uint16_t& address); // Logical AND
    void ASL();                        // Arithmetic Shift Left (Accumulator)
    void ASL(const uint16_t& address); // Arithmetic Shift Left
    void BCC(const uint16_t& address); // Branch if Carry Clear
    void BCS(const uint16_t& address); // Branch if Carry Set
    void BEQ(const uint16_t& address); // Branch if Equal
    void BIT(const uint16_t& address); // Bit Test
    void BMI(const uint16_t& address); // Branch if Minus
    void BNE(const uint16_t& address); // Branch if Not Equal
    void BPL(const uint16_t& address); // Branch if Positive
    void BRK();                        // Force Interrupt
    void BVC(const uint16_t& address); // Branch if Overflow Clear
    void BVS(const uint16_t& address); // Branch if Overflow Set
    void CLC();                        // Clear Carry Flag
    void CLD();                        // Clear Decimal Mode
    void CLI();                        // Clear Interrupt Disable
    void CLV();                        // Clear Overflow Flag
    void CMP(const uint16_t& address); // Compare
    void CPX(const uint16_t& address); // Compare X Register
    void CPY(const uint16_t& address); // Compare Y Register
    void DEC(const uint16_t& address); // Decrement Memory
    void DEX();                        // Decrement X Register
    void DEY();                        // Decrement Y Register
    void EOR(const uint16_t& address); // Exclusive OR
    void INC(const uint16_t& address); // Increment Memory
    void INX();                        // Increment X Register
    void INY();                        // Increment Y Register
    void JMP(const uint16_t& address); // Jump
    void JSR(const uint16_t& address); // Jump to Subroutine
    void LDA(const uint16_t& address); // Load Accumulator
    void LDX(const uint16_t& address); // Load X Register
    void LDY(const uint16_t& address); // Load Y Register
    void LSR();                        // Logical Shift Right (Accumulator)
    void LSR(const uint16_t& address); // Logical Shift Right
    void NOP();                        // No Operation
    void ORA(const uint16_t& address); // Logical Inclusive OR
    void PHA();                        // Push Accumulator
    void PHP();                        // Push Processor Status
    void PLA();                        // Pull Accumulator
    void PLP();                        // Pull Processor Status
    void ROL();                        // Rotate Left (Accumulator)
    void ROL(const uint16_t& address); // Rotate Left
    void ROR();                        // Rotate Right (Accumulator)
    void ROR(const uint16_t& address); // Rotate Right
    void RTI();                        // Return from Interrupt
    void RTS();                        // Return from Subroutine
    void SBC(const uint16_t& address); // Subtract with Carry
    void SEC();                        // Set Carry Flag
    void SED();                        // Set Decimal Flag
    void SEI();                        // Set Interrupt Disable
    void STA(const uint16_t& address); // Store Accumulator
    void STX(const uint16_t& address); // Store X Register
    void STY(const uint16_t& address); // Store Y Register
    void TAX();                        // Transfer Accumulator to X
    void TAY();                        // Transfer Accumulator to Y
    void TSX();                        // Transfer Stack Pointer to X
    void TXA();                        // Transfer X to Accumulator
    void TXS();                        // Transfer X to Stack Pointer
    void TYA();                        // Transfer Y to Accumulator
};