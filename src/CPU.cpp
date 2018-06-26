#include <iostream>

#include "CPU.hpp"
#include "Opcodes.hpp"

CPU::CPU(Memory* mem) {
    memory = mem;
}

void CPU::powerOn() {
    r_a = 0;
    r_x = 0;
    r_y = 0;

    pc = read16(0xFFFC);
    sp = 0xFD;

    r_p.set(INTERRUPT_DISABLE);
    r_p.set(BREAK_MODE_FLAG);
    r_p.set(UNUSED_BIT);
}

uint8_t CPU::fetch() {
    const uint8_t value = memory->read(pc);
    ++pc;
    return value;
}

uint16_t CPU::fetch16() {
    const uint16_t value = read16(pc);
    pc += 2;
    return value;
}

void CPU::push(const uint8_t& value) {
    memory->write(0x100 + sp, value);
    --sp;
}

uint8_t CPU::pop() {
    ++sp;
    return memory->read(0x100 + sp);
}

uint16_t CPU::read16(const uint16_t& address) {
    const uint16_t lo = memory->read(address);
    const uint16_t hi = memory->read(address + 1);
    return (hi << 8) | lo; // Little endian
}

void CPU::push16(const uint16_t& value) {
    const uint8_t hi = value >> 8;
    const uint8_t lo = value & 0x00FF;
    push(hi);
    push(lo);
}

uint16_t CPU::pop16() {
    const uint16_t lo = pop();
    const uint16_t hi = pop();
    return (hi << 8) | lo;
}

void CPU::setZeroFlag(const uint8_t& value) {
    const bool isZero = (value == 0);
    r_p.set(ZERO_FLAG, isZero);
}

void CPU::setNegativeFlag(const uint8_t& value) {
    const bool negativeBit = ((value) & 0b1000'0000);
    r_p.set(NEGATIVE_FLAG, negativeBit);
}

void CPU::step() {
    // TODO: Handle interrupts

    const uint8_t opcode = fetch();
    execute(opcode);
    
    cycles += cycle_table[opcode];
}

void CPU::execute(const uint8_t& opcode) {
    std::cout << "CPU::execute opcode: " << std::hex << (int)opcode << std::endl;  //d
    switch (opcode) {

        case 0x00:
            BRK();
            break;

        case 0x01:
            ORA(indexedIndirect());
            break;

        //case 0x02:
        //    // unofficial opcode: STP
        //    break;

        //case 0x03:
        //    // unofficial opcode
        //    break;

        //case 0x04:
        //    // unofficial opcode: NOP
        //    break;

        case 0x05:
            ORA(zeroPageX());
            break;

        case 0x06:
            ASL(zeroPage());
            break;

        //case 0x07:
        //    // unofficial opcode
        //    break;

        case 0x08:
            PHP();
            break;

        case 0x09:
            ORA(immediate());
            break;

        case 0x0A:
            ASL();
            break;

        //case 0x0B:
        //    // unofficial opcode
        //    break;

        //case 0x0C:
        //    // unofficial opcode: NOP
        //    break;

        case 0x0D:
            ORA(absolute());
            break;

        case 0x0E:
            ASL(absolute());
            break;

        //case 0x0F:
        //    // unofficial opcode
        //    break;

        case 0x10:
            BPL(relative());
            break;

        case 0x11:
            ORA(indirectIndexed());
            break;

        //case 0x12:
        //    // unofficial opcode: STP
        //    break;

        //case 0x13:
        //    // unofficial opcode
        //    break;

        //case 0x14:
        //    // unofficial opcode: NOP
        //    break;

        case 0x15:
            ORA(zeroPageX());
            break;

        case 0x16:
            ASL(zeroPageX());
            break;

        //case 0x17:
        //    // unofficial opcode
        //    break;

        case 0x18:
            CLC();
            break;

        case 0x19:
            ORA(absoluteY());
            break;

        //case 0x1A:
        //    // unofficial opcode: NOP
        //    break;

        //case 0x1B:
        //    // unofficial opcode
        //    break;

        //case 0x1C:
        //    // unofficial opcode: NOP
        //    break;

        case 0x1D:
            ORA(absoluteX());
            break;

        case 0x1E:
            ASL(absoluteX());
            break;

        //case 0x1F:
        //    // unofficial opcode
        //    break;

        case 0x20:
            JSR(absolute());
            break;

        case 0x21:
            AND(indexedIndirect());
            break;

        //case 0x22:
        //    // unofficial opcode: STP
        //    break;

        //case 0x23:
        //    // unofficial opcode
        //    break;

        case 0x24:
            BIT(zeroPage());
            break;

        case 0x25:
            AND(zeroPage());
            break;

        case 0x26:
            ROL(zeroPage());
            break;

        //case 0x27:
        //    // unofficial opcode
        //    break;

        case 0x28:
            PLP();
            break;

        case 0x29:
            AND(immediate());
            break;

        case 0x2A:
            ROL();
            break;

        //case 0x2B:
        //    // unofficial opcode
        //    break;

        case 0x2C:
            BIT(absolute());
            break;

        case 0x2D:
            AND(absolute());
            break;

        case 0x2E:
            ROL(absolute());
            break;

        //case 0x2F:
        //    // unofficial opcode
        //    break;

        case 0x30:
            BMI(relative());
            break;

        case 0x31:
            AND(indirectIndexed());
            break;

        //case 0x32:
        //    // unofficial opcode: STP
        //    break;

        //case 0x33:
        //    // unofficial opcode
        //    break;

        //case 0x34:
        //    // unofficial opcode: NOP
        //    break;

        case 0x35:
            AND(zeroPageX());
            break;

        case 0x36:
            ROL(zeroPageX());
            break;

        //case 0x37:
        //    // unofficial opcode
        //    break;

        case 0x38:
            SEC();
            break;

        case 0x39:
            AND(absoluteY());
            break;

        //case 0x3A:
        //    // unofficial opcode: NOP
        //    break;

        //case 0x3B:
        //    // unofficial opcode
        //    break;

        //case 0x3C:
        //    // unofficial opcode: NOP
        //    break;

        case 0x3D:
            AND(absoluteX());
            break;

        case 0x3E:
            ROL(absoluteX());
            break;

        //case 0x3F:
        //    // unofficial opcode
        //    break;

        case 0x40:
            RTI();
            break;

        case 0x41:
            EOR(indexedIndirect());
            break;

        //case 0x42:
        //    // unofficial opcode: STP
        //    break;

        //case 0x43:
        //    // unofficial opcode
        //    break;

        //case 0x44:
        //    // unofficial opcode: NOP
        //    break;

        case 0x45:
            EOR(zeroPage());
            break;

        case 0x46:
            LSR(zeroPage());
            break;

        //case 0x47:
        //    // unofficial opcode
        //    break;

        case 0x48:
            PHA();
            break;

        case 0x49:
            EOR(immediate());
            break;

        case 0x4A:
            LSR();
            break;

        //case 0x4B:
        //    // unofficial opcode
        //    break;

        case 0x4C:
            JMP(absolute());
            break;

        case 0x4D:
            EOR(absolute());
            break;

        case 0x4E:
            LSR(absolute());
            break;

        //case 0x4F:
        //    // unofficial opcode
        //    break;

        case 0x50:
            BVC(relative());
            break;

        case 0x51:
            EOR(indirectIndexed());
            break;

        //case 0x52:
        //    // unofficial opcode: STP
        //    break;

        //case 0x53:
        //    // unofficial opcode
        //    break;

        //case 0x54:
        //    // unofficial opcode: NOP
        //    break;

        case 0x55:
            EOR(zeroPageX());
            break;

        case 0x56:
            LSR(zeroPageX());
            break;

        //case 0x57:
        //    // unofficial opcode
        //    break;

        case 0x58:
            CLI();
            break;

        case 0x59:
            EOR(absoluteY());
            break;

        //case 0x5A:
        //    // unofficial opcode: NOP
        //    break;

        //case 0x5B:
        //    // unofficial opcode
        //    break;

        //case 0x5C:
        //    // unofficial opcode: NOP
        //    break;

        case 0x5D:
            EOR(absoluteX());
            break;

        case 0x5E:
            LSR(absoluteX());
            break;

        //case 0x5F:
        //    // unofficial opcode
        //    break;

        case 0x60:
            RTS();
            break;

        case 0x61:
            ADC(indexedIndirect());
            break;

        //case 0x62:
        //    // unofficial opcode: STP
        //    break;

        //case 0x63:
        //    // unofficial opcode
        //    break;

        //case 0x64:
        //    // unofficial opcode: NOP
        //    break;

        case 0x65:
            ADC(zeroPage());
            break;

        case 0x66:
            ROR(zeroPage());
            break;

        //case 0x67:
        //    // unofficial opcode
        //    break;

        case 0x68:
            PLA();
            break;

        case 0x69:
            ADC(immediate());
            break;

        case 0x6A:
            ROR();
            break;

        //case 0x6B:
        //    // unofficial opcode
        //    break;

        case 0x6C:
            JMP(indirect());
            break;

        case 0x6D:
            ADC(absolute());
            break;

        case 0x6E:
            ROR(absolute());
            break;

        //case 0x6F:
        //    // unofficial opcode
        //    break;

        case 0x70:
            BVS(relative());
            break;

        case 0x71:
            ADC(indirectIndexed());
            break;

        //case 0x72:
        //    // unofficial opcode: STP
        //    break;

        //case 0x73:
        //    // unofficial opcode
        //    break;

        //case 0x74:
        //    // unofficial opcode: NOP
        //    break;

        case 0x75:
            ADC(zeroPageX());
            break;

        case 0x76:
            ROR(zeroPageX());
            break;

        //case 0x77:
        //    // unofficial opcode
        //    break;

        case 0x78:
            SEI();
            break;

        case 0x79:
            ADC(absoluteY());
            break;

        //case 0x7A:
        //    // unofficial opcode: NOP
        //    break;

        //case 0x7B:
        //    // unofficial opcode
        //    break;

        //case 0x7C:
        //    // unofficial opcode: NOP
        //    break;

        case 0x7D:
            ADC(absoluteX());
            break;

        case 0x7E:
            ROR(absoluteX());
            break;

        //case 0x7F:
        //    // unofficial opcode
        //    break;

        //case 0x80:
        //    // unofficial opcode: NOP
        //    break;

        case 0x81:
            STA(indexedIndirect());
            break;

        //case 0x82:
        //    // unofficial opcode: NOP
        //    break;

        //case 0x83:
        //    // unofficial opcode
        //    break;

        case 0x84:
            STY(zeroPage());
            break;

        case 0x85:
            STA(zeroPage());
            break;

        case 0x86:
            STX(zeroPage());
            break;

        //case 0x87:
        //    // unofficial opcode
        //    break;

        case 0x88:
            DEY();
            break;

        //case 0x89:
        //    // unofficial opcode: NOP
        //    break;

        case 0x8A:
            TXA();
            break;

        //case 0x8B:
        //    // unofficial opcode
        //    break;

        case 0x8C:
            STY(absolute());
            break;

        case 0x8D:
            STA(absolute());
            break;

        case 0x8E:
            STX(absolute());
            break;

        //case 0x8F:
        //    // unofficial opcode
        //    break;

        case 0x90:
            BCC(relative());
            break;

        case 0x91:
            STA(indirectIndexed());
            break;

        //case 0x92:
        //    // unofficial opcode: STP
        //    break;

        //case 0x93:
        //    // unofficial opcode
        //    break;

        case 0x94:
            STY(zeroPageX());
            break;

        case 0x95:
            STA(zeroPageX());
            break;

        case 0x96:
            STX(zeroPageY());
            break;

        //case 0x97:
        //    // unofficial opcode
        //    break;

        case 0x98:
            TYA();
            break;

        case 0x99:
            STA(absoluteY());
            break;

        case 0x9A:
            TXS();
            break;

        //case 0x9B:
        //    // unofficial opcode
        //    break;

        //case 0x9C:
        //    // unofficial opcode: SHY
        //    break;

        case 0x9D:
            STA(absoluteX());
            break;

        //case 0x9E:
        //    // unofficial opcode: SHX
        //    break;

        //case 0x9F:
        //    // unofficial opcode
        //    break;

        case 0xA0:
            LDY(immediate());
            break;

        case 0xA1:
            LDA(indexedIndirect());
            break;

        case 0xA2:
            LDX(immediate());
            break;

        //case 0xA3:
        //    // unofficial opcode
        //    break;

        case 0xA4:
            LDY(zeroPage());
            break;

        case 0xA5:
            LDA(zeroPage());
            break;

        case 0xA6:
            LDX(zeroPage());
            break;

        //case 0xA7:
        //    // unofficial opcode
        //    break;

        case 0xA8:
            TAY();
            break;

        case 0xA9:
            LDA(immediate());
            break;

        case 0xAA:
            TAX();
            break;

        //case 0xAB:
        //    // unofficial opcode
        //    break;

        case 0xAC:
            LDY(absolute());
            break;

        case 0xAD:
            LDA(absolute());
            break;

        case 0xAE:
            LDX(absolute());
            break;

        //case 0xAF:
        //    // unofficial opcode
        //    break;

        case 0xB0:
            BCS(relative());
            break;

        case 0xB1:
            LDA(indirectIndexed());
            break;

        //case 0xB2:
        //    // unofficial opcode: STP
        //    break;

        //case 0xB3:
        //    // unofficial opcode
        //    break;

        case 0xB4:
            LDY(zeroPageX());
            break;

        case 0xB5:
            LDA(zeroPageX());
            break;

        case 0xB6:
            LDX(zeroPageY());
            break;

        //case 0xB7:
        //    // unofficial opcode
        //    break;

        case 0xB8:
            CLV();
            break;

        case 0xB9:
            LDA(absoluteY());
            break;

        case 0xBA:
            TSX();
            break;

        //case 0xBB:
        //    // unofficial opcode
        //    break;

        case 0xBC:
            LDY(absoluteX());
            break;

        case 0xBD:
            LDA(absoluteX());
            break;

        case 0xBE:
            LDX(absoluteY());
            break;

        //case 0xBF:
        //    // unofficial opcode
        //    break;

        case 0xC0:
            CPY(immediate());
            break;

        case 0xC1:
            CMP(indexedIndirect());
            break;

        //case 0xC2:
        //    // unofficial opcode: NOP
        //    break;

        //case 0xC3:
        //    // unofficial opcode
        //    break;

        case 0xC4:
            CPY(zeroPage());
            break;

        case 0xC5:
            CMP(zeroPage());
            break;

        case 0xC6:
            DEC(zeroPage());
            break;

        //case 0xC7:
        //    // unofficial opcode
        //    break;

        case 0xC8:
            INY();
            break;

        case 0xC9:
            CMP(immediate());
            break;

        case 0xCA:
            DEX();
            break;

        //case 0xCB:
        //    // unofficial opcode
        //    break;

        case 0xCC:
            CPY(absolute());
            break;

        case 0xCD:
            CMP(absolute());
            break;

        case 0xCE:
            DEC(absolute());
            break;

        //case 0xCF:
        //    // unofficial opcode
        //    break;

        case 0xD0:
            BNE(relative());
            break;

        case 0xD1:
            CMP(indirectIndexed());
            break;

        //case 0xD2:
        //    // unofficial opcode: STP
        //    break;

        //case 0xD3:
        //    // unofficial opcode
        //    break;

        //case 0xD4:
        //    // unofficial opcode: NOP
        //    break;

        case 0xD5:
            CMP(zeroPageX());
            break;

        case 0xD6:
            DEC(zeroPageX());
            break;

        //case 0xD7:
        //    // unofficial opcode
        //    break;

        case 0xD8:
            CLD();
            break;

        case 0xD9:
            CMP(absoluteY());
            break;

        //case 0xDA:
        //    // unofficial opcode: NOP
        //    break;

        //case 0xDB:
        //    // unofficial opcode
        //    break;

        //case 0xDC:
        //    // unofficial opcode: NOP
        //    break;

        case 0xDD:
            CMP(absoluteX());
            break;

        case 0xDE:
            DEC(absoluteX());
            break;

        //case 0xDF:
        //    // unofficial opcode
        //    break;

        case 0xE0:
            CPX(immediate());
            break;

        case 0xE1:
            SBC(indexedIndirect());
            break;

        //case 0xE2:
        //    // unofficial opcode: NOP
        //    break;

        //case 0xE3:
        //    // unofficial opcode
        //    break;

        case 0xE4:
            CPX(zeroPage());
            break;

        case 0xE5:
            SBC(zeroPage());
            break;

        case 0xE6:
            INC(zeroPage());
            break;

        //case 0xE7:
        //    // unofficial opcode
        //    break;

        case 0xE8:
            INX();
            break;

        case 0xE9:
            SBC(immediate());
            break;

        case 0xEA:
            NOP();
            break;

        //case 0xEB:
        //    // unofficial opcode
        //    break;

        case 0xEC:
            CPX(absolute());
            break;

        case 0xED:
            SBC(absolute());
            break;

        case 0xEE:
            INC(absolute());
            break;

        //case 0xEF:
        //    // unofficial opcode
        //    break;

        case 0xF0:
            BEQ(relative());
            break;

        case 0xF1:
            SBC(indirectIndexed());
            break;

        //case 0xF2:
        //    // unofficial opcode: STP
        //    break;

        //case 0xF3:
        //    // unofficial opcode
        //    break;

        //case 0xF4:
        //    // unofficial opcode: NOP
        //    break;

        case 0xF5:
            SBC(zeroPageX());
            break;

        case 0xF6:
            INC(zeroPageX());
            break;

        //case 0xF7:
        //    // unofficial opcode
        //    break;

        case 0xF8:
            SED();
            break;

        case 0xF9:
            SBC(absolute());
            break;

        //case 0xFA:
        //    // unofficial opcode: NOP
        //    break;

        //case 0xFB:
        //    // unofficial opcode
        //    break;

        //case 0xFC:
        //    // unofficial opcode: NOP
        //    break;

        case 0xFD:
            SBC(absoluteX());
            break;

        case 0xFE:
            INC(absoluteX());
            break;

        //case 0xFF:
        //    // unofficial opcode
        //    break;

        default:
            std::cerr << "Unsupported instruction: " << instruction_table[opcode]
                << ". Opcode: " << std::hex << (int)opcode << std::endl;
            break;
    }
}



void CPU::ADC(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const unsigned int sum = (int)r_a + (int)value + r_p.test(CARRY_FLAG);
    r_p.set(CARRY_FLAG,  // Unsigned overflow
            sum & 0b1'0000'0000);
    r_p.set(OVERFLOW_FLAG, // Signed overflow
            ~(r_a ^ value) & (r_a ^ sum) & 0b1000'0000);
    r_a = (uint8_t)sum;
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::AND(const uint16_t& address) {
    r_a &= memory->read(address);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::ASL() {
    const uint8_t carry_bit = r_a & 0b1000'0000;
    r_a <<= 1;
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::ASL(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t carry_bit = value & 0b1000'0000;
    const uint8_t result = value << 1;
    memory->write(address, result);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::BCC(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (!r_p.test(CARRY_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BCS(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (r_p.test(CARRY_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BEQ(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (r_p.test(ZERO_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BIT(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    r_p.set(OVERFLOW_FLAG,
            ((value >> 6) & 1));
    setZeroFlag(value & r_a);
    setNegativeFlag(value);
}

void CPU::BMI(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (r_p.test(NEGATIVE_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BNE(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (!r_p.test(ZERO_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BPL(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (!r_p.test(NEGATIVE_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BRK() {
    push16(pc);
    push((uint8_t)r_p.to_ulong());
    pc = read16(0xFFFE);
    r_p.set(BREAK_MODE_FLAG);
}

void CPU::BVC(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (!r_p.test(OVERFLOW_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::BVS(const uint16_t& address) {
    const int8_t offset = memory->read(address);
    if (r_p.test(OVERFLOW_FLAG)) {
        pc = (int)pc + offset; }
}

void CPU::CLC() {
    r_p.reset(CARRY_FLAG);
}

void CPU::CLD() {
    r_p.reset(DECIMAL_MODE);
}

void CPU::CLI() {
    r_p.reset(INTERRUPT_DISABLE);
}

void CPU::CLV() {
    r_p.reset(OVERFLOW_FLAG);
}

void CPU::CMP(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t result = r_a - value;
    r_p.set(CARRY_FLAG, (result >= 0));
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::CPX(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t result = r_x - value;
    r_p.set(CARRY_FLAG, (result >= 0));
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::CPY(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t result = r_y - value;
    r_p.set(CARRY_FLAG, (result >= 0));
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::DEC(const uint16_t& address) {
    const uint8_t result = memory->read(address) - 1;
    memory->write(address, result);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::DEX() {
    --r_x;
    setZeroFlag(r_x);
    setNegativeFlag(r_x);
}

void CPU::DEY() {
    --r_y;
    setZeroFlag(r_y);
    setNegativeFlag(r_y);
}

void CPU::EOR(const uint16_t& address) {
    r_a ^= memory->read(address);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::INC(const uint16_t& address) {
    const uint8_t result = memory->read(address) + 1;
    memory->write(address, result);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::INX() {
    ++r_x;
    setZeroFlag(r_x);
    setNegativeFlag(r_x);
}

void CPU::INY() {
    ++r_y;
    setZeroFlag(r_y);
    setNegativeFlag(r_y);
}

void CPU::JMP(const uint16_t& address) {
    pc = address;
}

void CPU::JSR(const uint16_t& address) {
    push16(pc - 1);
    pc = address;
}

void CPU::LDA(const uint16_t& address) {
    r_a = memory->read(address);

    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::LDX(const uint16_t& address) {
    r_x = memory->read(address);

    setZeroFlag(r_x);
    setNegativeFlag(r_x);
}

void CPU::LDY(const uint16_t& address) {
    r_y = memory->read(address);

    setZeroFlag(r_y);
    setNegativeFlag(r_y);
}

void CPU::LSR() {
    const uint8_t carry_bit = r_a & 0b0000'0001;
    r_a >>= 1;
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::LSR(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t carry_bit = value & 0b0000'0001;
    const uint8_t result = value >> 1;
    memory->write(address, result);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::NOP() {
    // Do nothing.
}

void CPU::ORA(const uint16_t& address) {
    r_a |= memory->read(address);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::PHA() {
    push(r_a);
}

void CPU::PHP() {
    push((uint8_t)r_p.to_ulong());
}

void CPU::PLA() {
    r_a = pop();
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::PLP() {
    r_p = pop();
}

void CPU::ROL() {
    const uint8_t carry_bit = r_a & 0b1000'0000;
    r_a = (r_a << 1) & r_p.test(CARRY_FLAG);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::ROL(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t carry_bit = value & 0b1000'0000;
    const uint8_t result = (value << 1) & r_p.test(CARRY_FLAG);
    memory->write(address, result);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::ROR() {
    const uint8_t carry_bit = r_a & 0b0000'0001;
    r_a = (r_a >> 1) & (r_p.test(CARRY_FLAG) << 7);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::ROR(const uint16_t& address) {
    const uint8_t value = memory->read(address);
    const uint8_t carry_bit = value & 0b0000'0001;
    const uint8_t result = (value >> 1) & (r_p.test(CARRY_FLAG) << 7);
    memory->write(address, result);
    r_p.set(CARRY_FLAG, carry_bit);
    setZeroFlag(result);
    setNegativeFlag(result);
}

void CPU::RTI() {
    r_p = pop();
    pc = pop16();
}

void CPU::RTS() {
    pc = pop16() + 1;
}

void CPU::SBC(const uint16_t& address) {
    const uint8_t value = memory->read(address) ^ 0xFF;
    const unsigned int sum = (int)r_a + (int)value + r_p.test(CARRY_FLAG);
    r_p.set(CARRY_FLAG,  // Unsigned overflow
        sum & 0b1'0000'0000);
    r_p.set(OVERFLOW_FLAG, // Signed overflow
        ~(r_a ^ value) & (r_a ^ sum) & 0b1000'0000);
    r_a = (uint8_t)sum;
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::SEC() {
    r_p.set(CARRY_FLAG);
}

void CPU::SED() {
    r_p.set(DECIMAL_MODE);
}

void CPU::SEI() {
    r_p.set(INTERRUPT_DISABLE);
}

void CPU::STA(const uint16_t& address) {
    memory->write(address, r_a);
}

void CPU::STX(const uint16_t& address) {
    memory->write(address, r_x);
}

void CPU::STY(const uint16_t& address) {
    memory->write(address, r_y);
}

void CPU::TAX() {
    r_x = r_a;
    setZeroFlag(r_x);
    setNegativeFlag(r_x);
}

void CPU::TAY() {
    r_y = r_a;
    setZeroFlag(r_y);
    setNegativeFlag(r_y);
}

void CPU::TSX() {
    r_x = sp;

    setZeroFlag(r_x);
    setNegativeFlag(r_x);
}

void CPU::TXA() {
    r_a = r_x;
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}

void CPU::TXS() {
    sp = r_x;
}

void CPU::TYA() {
    r_a = r_x;
    setZeroFlag(r_a);
    setNegativeFlag(r_a);
}