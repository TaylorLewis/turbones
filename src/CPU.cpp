#include <iostream>

#include "CPU.hpp"
#include "Opcodes.hpp"

CPU::CPU(Memory* mem) {
    memory = mem;

    r_a = 0;
    r_x = 0;
    r_y = 0;

    r_sp = 0xFD;

    r_p = 0b0011'0100;

    r_pc = 0x8000;
}

void CPU::step() {
    // TODO: Handle interrupts

    const uint8_t opcode = memory->read(r_pc);
    execute(opcode);
    
    cycles += cycle_table[opcode];
}

void CPU::execute(const uint8_t& opcode) {
    std::cout << "CPU::execute opcode: " << std::hex << (int)opcode << std::endl;  //d
    switch (opcode) {

        //case 0x00:
        //    implied(&BRK);
        //    break;

        //case 0x01:
        //    indexedIndirect(&CPU::ORA);
        //    break;

        //case 0x02:
        //    // STP
        //    break;

        //case 0x03:
        //    // illegal opcode
        //    break;

        //case 0x04:
        //    // NOP
        //    break;

        //case 0x05:
        //    zeroPageX(&CPU::ORA);
        //    break;

        //case 0x06:
        //    zeroPage(&CPU::ASL);
        //    break;

        //case 0x07:
        //    // illegal opcode
        //    break;

        //case 0x08:
        //    implied(&CPU::PHP);
        //    break;

        //case 0x09:
        //    immediate(&CPU::ORA);
        //    break;

        //case 0x0A:
        //    implied(&CPU::ASL);
        //    break;

        //case 0x0B:
        //    // illegal opcode
        //    break;

        //case 0x0C:
        //    // NOP
        //    break;

        //case 0x0D:
        //    absolute(&CPU::ORA);
        //    break;

        //case 0x0E:
        //    absolute(&CPU::ASL);
        //    break;

        //case 0x0F:
        //    // illegal opcode
        //    break;

        //case 0x10:
        //    relative(&CPU::BPL);
        //    break;

        //case 0x11:
        //    indirectIndexed(&CPU::ORA);
        //    break;

        //case 0x12:
        //    // STP
        //    break;

        //case 0x13:
        //    // illegal opcode
        //    break;

        //case 0x14:
        //    // NOP
        //    break;

        //case 0x15:
        //    zeroPageX(&CPU::ORA);
        //    break;

        //case 0x16:
        //    zeroPageX(&CPU::ASL);
        //    break;

        //case 0x17:
        //    // illegal opcode
        //    break;

        //case 0x18:
        //    implied(&CPU::CLC);
        //    break;

        //case 0x19:
        //    absoluteY(&CPU::ORA);
        //    break;

        //case 0x1A:
        //    // NOP
        //    break;

        //case 0x1B:
        //    // illegal opcode
        //    break;

        //case 0x1C:
        //    // NOP
        //    break;

        //case 0x1D:
        //    absoluteX(&CPU::ORA);
        //    break;

        //case 0x1E:
        //    absoluteX(&CPU::ASL);
        //    break;

        //case 0x1F:
        //    // illegal opcode
        //    break;

        //case 0x20:
        //    absolute(&CPU::JSR);
        //    break;

        //case 0x21:
        //    indexedIndirect(&CPU::AND);
        //    break;

        //case 0x22:
        //    // STP
        //    break;

        //case 0x23:
        //    // illegal opcode
        //    break;

        //case 0x24:
        //    zeroPage(&CPU::BIT);
        //    break;

        //case 0x25:
        //    zeroPage(&CPU::AND);
        //    break;

        //case 0x26:
        //    zeroPage(&CPU::ROL);
        //    break;

        //case 0x27:
        //    // illegal opcode
        //    break;

        //case 0x28:
        //    implied(&CPU::PLP);
        //    break;

        //case 0x29:
        //    immediate(&CPU::AND);
        //    break;

        //case 0x2A:
        //    implied(&CPU::ROL);
        //    break;

        //case 0x2B:
        //    // illegal opcode
        //    break;

        //case 0x2C:
        //    absolute(&CPU::BIT);
        //    break;

        //case 0x2D:
        //    absolute(&CPU::AND);
        //    break;

        //case 0x2E:
        //    absolute(&CPU::ROL);
        //    break;

        //case 0x2F:
        //    // illegal opcode
        //    break;

        //case 0x30:
        //    relative(&CPU::BMI);
        //    break;

        //case 0x31:
        //    indirectIndexed(AND);
        //    break;

        //case 0x32:
        //    // STP
        //    break;

        //case 0x33:
        //    // illegal opcode
        //    break;

        //case 0x34:
        //    // NOP
        //    break;

        //case 0x35:
        //    zeroPageX(&CPU::AND);
        //    break;

        //case 0x36:
        //    zeroPageX(&CPU::ROL);
        //    break;

        //case 0x37:
        //    // illegal opcode
        //    break;

        //case 0x38:
        //    implied(&CPU::SEC);
        //    break;

        //case 0x39:
        //    absoluteY(&CPU::AND);
        //    break;

        //case 0x3A:
        //    // NOP
        //    break;

        //case 0x3B:
        //    // illegal opcode
        //    break;

        //case 0x3C:
        //    // NOP
        //    break;

        //case 0x3D:
        //    absoluteX(&CPU::AND);
        //    break;

        //case 0x3E:
        //    absoluteX(&CPU::ROL);
        //    break;

        //case 0x3F:
        //    // illegal opcode
        //    break;

        //case 0x40:
        //    implied(&CPU::RTI);
        //    break;

        //case 0x41:
        //    indexedIndirect(&CPU::EOR);
        //    break;

        //case 0x42:
        //    // STP
        //    break;

        //case 0x43:
        //    // illegal opcode
        //    break;

        //case 0x44:
        //    // NOP
        //    break;

        //case 0x45:
        //    zeroPage(&CPU::EOR);
        //    break;

        //case 0x46:
        //    zeroPage(&CPU::LSR);
        //    break;

        //case 0x47:
        //    // illegal opcode
        //    break;

        case 0x48:
            implied(&CPU::PHA);
            break;

        //case 0x49:
        //    immediate(&CPU::EOR);
        //    break;

        //case 0x4A:
        //    implied(&CPU::LSR);
        //    break;

        //case 0x4B:
        //    // illegal opcode
        //    break;

        //case 0x4C:
        //    absolute(&CPU::JMP);
        //    break;

        //case 0x4D:
        //    absolute(&CPU::EOR);
        //    break;

        //case 0x4E:
        //    absolute(&CPU::LSR);
        //    break;

        //case 0x4F:
        //    // illegal opcode
        //    break;

        //case 0x50:
        //    relative(&CPU::BVC);
        //    break;

        //case 0x51:
        //    indirectIndexed(&CPU::EOR);
        //    break;

        //case 0x52:
        //    // STP
        //    break;

        //case 0x53:
        //    // illegal opcode
        //    break;

        //case 0x54:
        //    // NOP
        //    break;

        //case 0x55:
        //    zeroPageX(&CPU::EOR);
        //    break;

        //case 0x56:
        //    zeroPageX(&CPU::LSR);
        //    break;

        //case 0x57:
        //    // illegal opcode
        //    break;

        //case 0x58:
        //    implied(&CPU::CLI);
        //    break;

        //case 0x59:
        //    absoluteY(&CPU::EOR);
        //    break;

        //case 0x5A:
        //    // NOP
        //    break;

        //case 0x5B:
        //    // illegal opcode
        //    break;

        //case 0x5C:
        //    // NOP
        //    break;

        //case 0x5D:
        //    absoluteX(&CPU::EOR);
        //    break;

        //case 0x5E:
        //    absoluteX(&CPU::LSR);
        //    break;

        //case 0x5F:
        //    // illegal opcode
        //    break;

        //case 0x60:
        //    implied(&CPU::RTS);
        //    break;

        //case 0x61:
        //    indexedIndirect(&CPU::ADC);
        //    break;

        //case 0x62:
        //    // STP
        //    break;

        //case 0x63:
        //    // illegal opcode
        //    break;

        //case 0x64:
        //    // NOP
        //    break;

        //case 0x65:
        //    zeroPage(&CPU::ADC);
        //    break;

        //case 0x66:
        //    zeroPage(&CPU::ROR);
        //    break;

        //case 0x67:
        //    // illegal opcode
        //    break;

        //case 0x68:
        //    implied(&CPU::PLA);
        //    break;

        //case 0x69:
        //    immediate(&CPU::ADC);
        //    break;

        //case 0x6A:
        //    implied(&CPU::ROR);
        //    break;

        //case 0x6B:
        //    // illegal opcode
        //    break;

        //case 0x6C:
        //    indirect(&CPU::JMP);
        //    break;

        //case 0x6D:
        //    absolute(&CPU::ADC);
        //    break;

        //case 0x6E:
        //    absolute(&CPU::ROR);
        //    break;

        //case 0x6F:
        //    // illegal opcode
        //    break;

        //case 0x70:
        //    relative(&CPU::BVS);
        //    break;

        //case 0x71:
        //    indirectIndexed(&CPU::ADC);
        //    break;

        //case 0x72:
        //    // STP
        //    break;

        //case 0x73:
        //    // illegal opcode
        //    break;

        //case 0x74:
        //    // NOP
        //    break;

        //case 0x75:
        //    zeroPageX(&CPU::ADC);
        //    break;

        //case 0x76:
        //    zeroPageX(&CPU::ROR);
        //    break;

        //case 0x77:
        //    // illegal opcode
        //    break;

        //case 0x78:
        //    implied(&CPU::SEI);
        //    break;

        //case 0x79:
        //    absoluteY(&CPU::ADC);
        //    break;

        //case 0x7A:
        //    // NOP
        //    break;

        //case 0x7B:
        //    // illegal opcode
        //    break;

        //case 0x7C:
        //    // NOP
        //    break;

        //case 0x7D:
        //    absoluteX(&CPU::ADC);
        //    break;

        //case 0x7E:
        //    absoluteX(&CPU::ROR);
        //    break;

        //case 0x7F:
        //    // illegal opcode
        //    break;

        //case 0x80:
        //    // NOP
        //    break;

        //case 0x81:
        //    indexedIndirect(&CPU::STA);
        //    break;

        //case 0x82:
        //    // NOP
        //    break;

        //case 0x83:
        //    // illegal opcode
        //    break;

        //case 0x84:
        //    zeroPage(&CPU::STY);
        //    break;

        //case 0x85:
        //    zeroPage(&CPU::STA);
        //    break;

        //case 0x86:
        //    zeroPage(&CPU::STX);
        //    break;

        //case 0x87:
        //    // illegal opcode
        //    break;

        //case 0x88:
        //    implied(&CPU::DEY);
        //    break;

        //case 0x89:
        //    // NOP
        //    break;

        //case 0x8A:
        //    implied(&CPU::TXA);
        //    break;

        //case 0x8B:
        //    // illegal opcode
        //    break;

        //case 0x8C:
        //    absolute(&CPU::STY);
        //    break;

        //case 0x8D:
        //    absolute(&CPU::STA);
        //    break;

        //case 0x8E:
        //    absolute(&CPU::STX);
        //    break;

        //case 0x8F:
        //    // illegal opcode
        //    break;

        //case 0x90:
        //    relative(&CPU::BCC);
        //    break;

        //case 0x91:
        //    indirectIndexed(&CPU::STA);
        //    break;

        //case 0x92:
        //    // STP
        //    break;

        //case 0x93:
        //    // illegal opcode
        //    break;

        //case 0x94:
        //    zeroPageX(&CPU::STY);
        //    break;

        //case 0x95:
        //    zeroPageX(&CPU::STA);
        //    break;

        //case 0x96:
        //    zeroPageY(&CPU::STX);
        //    break;

        //case 0x97:
        //    // illegal opcode
        //    break;

        //case 0x98:
        //    implied(&CPU::TYA);
        //    break;

        //case 0x99:
        //    absoluteY(&CPU::STA);
        //    break;

        //case 0x9A:
        //    implied(&CPU::TXS);
        //    break;

        //case 0x9B:
        //    // illegal opcode
        //    break;

        //case 0x9C:
        //    // SHY
        //    break;

        //case 0x9D:
        //    absoluteX(&CPU::STA);
        //    break;

        //case 0x9E:
        //    // SHX
        //    break;

        //case 0x9F:
        //    // illegal opcode
        //    break;

        //case 0xA0:
        //    immediate(&CPU::LDY);
        //    break;

        //case 0xA1:
        //    indexedIndirect(&CPU::LDA);
        //    break;

        //case 0xA2:
        //    immediate(&CPU::LDX);
        //    break;

        //case 0xA3:
        //    // illegal opcode
        //    break;

        //case 0xA4:
        //    zeroPage(&CPU::LDY);
        //    break;

        //case 0xA5:
        //    zeroPage(&CPU::LDA);
        //    break;

        //case 0xA6:
        //    zeroPage(&CPU::LDX);
        //    break;

        //case 0xA7:
        //    // illegal opcode
        //    break;

        //case 0xA8:
        //    implied(&CPU::TAY);
        //    break;

        //case 0xA9:
        //    immediate(&CPU::LDA);
        //    break;

        //case 0xAA:
        //    implied(&CPU::TAX);
        //    break;

        //case 0xAB:
        //    // illegal opcode
        //    break;

        //case 0xAC:
        //    absolute(&CPU::LDY);
        //    break;

        //case 0xAD:
        //    absolute(&CPU::LDA);
        //    break;

        //case 0xAE:
        //    absolute(&CPU::LDX);
        //    break;

        //case 0xAF:
        //    // illegal opcode
        //    break;

        //case 0xB0:
        //    relative(&CPU::BCS);
        //    break;

        //case 0xB1:
        //    indirectIndexed(&CPU::LDA);
        //    break;

        //case 0xB2:
        //    // STP
        //    break;

        //case 0xB3:
        //    // illegal opcode
        //    break;

        //case 0xB4:
        //    zeroPageX(&CPU::LDY);
        //    break;

        //case 0xB5:
        //    zeroPageX(&CPU::LDA);
        //    break;

        //case 0xB6:
        //    zeroPageY(&CPU::LDX);
        //    break;

        //case 0xB7:
        //    // illegal opcode
        //    break;

        //case 0xB8:
        //    implied(&CPU::CLV);
        //    break;

        //case 0xB9:
        //    absoluteY(&CPU::LDA);
        //    break;

        //case 0xBA:
        //    implied(&CPU::TSX);
        //    break;

        //case 0xBB:
        //    // illegal opcode
        //    break;

        //case 0xBC:
        //    absoluteX(&CPU::LDY);
        //    break;

        //case 0xBD:
        //    absoluteX(&CPU::LDA);
        //    break;

        //case 0xBE:
        //    absoluteY(&CPU::LDX);
        //    break;

        //case 0xBF:
        //    // illegal opcode
        //    break;

        //case 0xC0:
        //    immediate(&CPU::CPY);
        //    break;

        //case 0xC1:
        //    indexedIndirect(&CPU::CMP);
        //    break;

        //case 0xC2:
        //    // NOP
        //    break;

        //case 0xC3:
        //    // illegal opcode
        //    break;

        //case 0xC4:
        //    zeroPage(&CPU::CPY);
        //    break;

        //case 0xC5:
        //    zeroPage(&CPU::CMP);
        //    break;

        //case 0xC6:
        //    zeroPage(&CPU::DEC);
        //    break;

        //case 0xC7:
        //    // illegal opcode
        //    break;

        //case 0xC8:
        //    implied(&CPU::INY);
        //    break;

        //case 0xC9:
        //    immediate(&CPU::CMP);
        //    break;

        //case 0xCA:
        //    implied(&CPU::DEX);
        //    break;

        //case 0xCB:
        //    // illegal opcode
        //    break;

        //case 0xCC:
        //    absolute(&CPU::CPY);
        //    break;

        //case 0xCD:
        //    absolute(&CPU::CMP);
        //    break;

        //case 0xCE:
        //    absolute(&CPU::DEC);
        //    break;

        //case 0xCF:
        //    // illegal opcode
        //    break;

        //case 0xD0:
        //    relative(&CPU::BNE);
        //    break;

        //case 0xD1:
        //    indirectIndexed(&CPU::CMP);
        //    break;

        //case 0xD2:
        //    // STP
        //    break;

        //case 0xD3:
        //    // illegal opcode
        //    break;

        //case 0xD4:
        //    // NOP
        //    break;

        //case 0xD5:
        //    zeroPageX(&CPU::CMP);
        //    break;

        //case 0xD6:
        //    zeroPageX(&CPU::DEC);
        //    break;

        //case 0xD7:
        //    // illegal opcode
        //    break;

        //case 0xD8:
        //    implied(&CPU::CLD);
        //    break;

        //case 0xD9:
        //    absoluteY(&CPU::CMP);
        //    break;

        //case 0xDA:
        //    // NOP
        //    break;

        //case 0xDB:
        //    // illegal opcode
        //    break;

        //case 0xDC:
        //    // NOP
        //    break;

        //case 0xDD:
        //    absoluteX(&CPU::CMP);
        //    break;

        //case 0xDE:
        //    absoluteX(&CPU::DEC);
        //    break;

        //case 0xDF:
        //    // illegal opcode
        //    break;

        //case 0xE0:
        //    immediate(&CPU::CPX);
        //    break;

        //case 0xE1:
        //    indexedIndirect(&CPU::SBC);
        //    break;

        //case 0xE2:
        //    // NOP
        //    break;

        //case 0xE3:
        //    // illegal opcode
        //    break;

        //case 0xE4:
        //    zeroPage(&CPU::CPX);
        //    break;

        //case 0xE5:
        //    zeroPage(&CPU::SBC);
        //    break;

        //case 0xE6:
        //    zeroPage(&CPU::INC);
        //    break;

        //case 0xE7:
        //    // illegal opcode
        //    break;

        //case 0xE8:
        //    implied(&CPU::INX);
        //    break;

        //case 0xE9:
        //    immediate(&CPU::SBC);
        //    break;

        //case 0xEA:
        //    // NOP
        //    break;

        //case 0xEB:
        //    // illegal opcode
        //    break;

        //case 0xEC:
        //    absolute(&CPU::CPX);
        //    break;

        //case 0xED:
        //    absolute(&CPU::SBC);
        //    break;

        //case 0xEE:
        //    absolute(&CPU::INC);
        //    break;

        //case 0xEF:
        //    // illegal opcode
        //    break;

        //case 0xF0:
        //    relative(&CPU::BEQ);
        //    break;

        //case 0xF1:
        //    indirectIndexed(&CPU::SBC);
        //    break;

        //case 0xF2:
        //    // STP
        //    break;

        //case 0xF3:
        //    // illegal opcode
        //    break;

        //case 0xF4:
        //    // NOP
        //    break;

        //case 0xF5:
        //    zeroPageX(&CPU::SBC);
        //    break;

        //case 0xF6:
        //    zeroPageX(&CPU::INC);
        //    break;

        //case 0xF7:
        //    // illegal opcode
        //    break;

        //case 0xF8:
        //    implied(&CPU::SED);
        //    break;

        //case 0xF9:
        //    absolute(&CPU::SBC);
        //    break;

        //case 0xFA:
        //    // NOP
        //    break;

        //case 0xFB:
        //    // illegal opcode
        //    break;

        //case 0xFC:
        //    // NOP
        //    break;

        //case 0xFD:
        //    absoluteX(&CPU::SBC);
        //    break;

        //case 0xFE:
        //    absoluteX(&CPU::INC);
        //    break;

        //case 0xFF:
        //    // illegal opcode
        //    break;

        default:
            std::cerr << "Unsupported instruction: " << instruction_table[opcode]
                << ". Opcode: " << std::hex << (int)opcode << std::endl;
    }
}

uint8_t CPU::fetch() {
    const uint8_t value = memory->read(r_pc);
    ++r_pc;
    return value;
}

uint16_t CPU::fetch16() {
    const uint16_t value = read16(r_pc);
    r_pc += 2;
    return value;
}

void CPU::push(const uint8_t& value) {
    memory->write(0x100 + r_sp, value);
    --r_sp;
}

uint8_t CPU::pop() {
    ++r_sp;
    return memory->read(0x100 + r_sp);
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



void CPU::ADC()
{
}

void CPU::AND()
{
}

void CPU::ASL()
{
}

void CPU::BCC()
{
}

void CPU::BCS()
{
}

void CPU::BEQ()
{
}

void CPU::BIT()
{
}

void CPU::BMI()
{
}

void CPU::BNE()
{
}

void CPU::BPL()
{
}

void CPU::BRK()
{
}

void CPU::BVC()
{
}

void CPU::BVS()
{
}

void CPU::CLC()
{
}

void CPU::CLD()
{
}

void CPU::CLI()
{
}

void CPU::CLV()
{
}

void CPU::CMP()
{
}

void CPU::CPX()
{
}

void CPU::CPY()
{
}

void CPU::DEC()
{
}

void CPU::DEX()
{
}

void CPU::DEY()
{
}

void CPU::EOR()
{
}

void CPU::INC()
{
}

void CPU::INX()
{
}

void CPU::INY()
{
}

void CPU::JMP()
{
}

void CPU::JSR()
{
}

void CPU::LDA()
{
}

void CPU::LDX()
{
}

void CPU::LDY()
{
}

void CPU::LSR()
{
}

void CPU::NOP()
{
}

void CPU::ORA()
{
}

void CPU::PHA() {
    push(r_sp);
}

void CPU::PHP()
{
}

void CPU::PLA()
{
}

void CPU::PLP()
{
}

void CPU::ROL()
{
}

void CPU::ROR()
{
}

void CPU::RTI()
{
}

void CPU::RTS()
{
}

void CPU::SBC()
{
}

void CPU::SEC()
{
}

void CPU::SED()
{
}

void CPU::SEI()
{
}

void CPU::STA()
{
}

void CPU::STX()
{
}

void CPU::STY()
{
}

void CPU::TAX()
{
}

void CPU::TAY()
{
}

void CPU::TSX()
{
}

void CPU::TXA()
{
}

void CPU::TXS()
{
}

void CPU::TYA()
{
}