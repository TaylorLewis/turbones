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



    case 0x48:
        implied(&CPU::PHA);
        break;



        default:
            std::cerr << "Unsupported opcode: " << instruction_table[opcode] << std::endl;
    }
}

void CPU::push(uint8_t & value) {
    memory->write(0x100 + r_sp, value);
    --r_sp;
}

uint8_t CPU::pop() {
    ++r_sp;
    return memory->read(0x100 + r_sp);
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