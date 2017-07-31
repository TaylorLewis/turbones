#pragma once

#include <stdint.h>
#include <array>
#include <string>

// Names of each instruction, indexed by opcode value.
const std::array<std::string, 0x100> instruction_table
{
/*0x00*/ "BRK", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
         "PHP", "ORA", "ASL", "ANC", "NOP", "ORA", "ASL", "SLO",
/*0x10*/ "BPL", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
         "CLC", "ORA", "NOP", "SLO", "NOP", "ORA", "ASL", "SLO",
/*0x20*/ "JSR", "AND", "KIL", "RLA", "BIT", "AND", "ROL", "RLA",
         "PLP", "AND", "ROL", "ANC", "BIT", "AND", "ROL", "RLA",
/*0x30*/ "BMI", "AND", "KIL", "RLA", "NOP", "AND", "ROL", "RLA",
         "SEC", "AND", "NOP", "RLA", "NOP", "AND", "ROL", "RLA",
/*0x40*/ "RTI", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
         "PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
/*0x50*/ "BVC", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
         "CLI", "EOR", "NOP", "SRE", "NOP", "EOR", "LSR", "SRE",
/*0x60*/ "RTS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
         "PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
/*0x70*/ "BVS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
         "SEI", "ADC", "NOP", "RRA", "NOP", "ADC", "ROR", "RRA",
/*0x80*/ "NOP", "STA", "NOP", "SAX", "STY", "STA", "STX", "SAX",
         "DEY", "NOP", "TXA", "XAA", "STY", "STA", "STX", "SAX",
/*0x90*/ "BCC", "STA", "KIL", "AHX", "STY", "STA", "STX", "SAX",
         "TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
/*0xA0*/ "LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX",
         "TAY", "LDA", "TAX", "LAX", "LDY", "LDA", "LDX", "LAX",
/*0xB0*/ "BCS", "LDA", "KIL", "LAX", "LDY", "LDA", "LDX", "LAX",
         "CLV", "LDA", "TSX", "LAS", "LDY", "LDA", "LDX", "LAX",
/*0xC0*/ "CPY", "CMP", "NOP", "DCP", "CPY", "CMP", "DEC", "DCP",
         "INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
/*0xD0*/ "BNE", "CMP", "KIL", "DCP", "NOP", "CMP", "DEC", "DCP",
         "CLD", "CMP", "NOP", "DCP", "NOP", "CMP", "DEC", "DCP",
/*0xE0*/ "CPX", "SBC", "NOP", "ISC", "CPX", "SBC", "INC", "ISC",
         "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISC",
/*0xF0*/ "BEQ", "SBC", "KIL", "ISC", "NOP", "SBC", "INC", "ISC",
         "SED", "SBC", "NOP", "ISC", "NOP", "SBC", "INC", "ISC",
};

// Number of cycles each operation takes, indexed by opcode value.
constexpr std::array<uint8_t, 0x100> cycle_table =
{
/*0x00*/ 7,6,2,8,3,3,5,5,3,2,2,2,4,4,6,6,
/*0x10*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x20*/ 6,6,2,8,3,3,5,5,4,2,2,2,4,4,6,6,
/*0x30*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x40*/ 6,6,2,8,3,3,5,5,3,2,2,2,3,4,6,6,
/*0x50*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x60*/ 6,6,2,8,3,3,5,5,4,2,2,2,5,4,6,6,
/*0x70*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x80*/ 2,6,2,6,3,3,3,3,2,2,2,2,4,4,4,4,
/*0x90*/ 2,6,2,6,4,4,4,4,2,5,2,5,5,5,5,5,
/*0xA0*/ 2,6,2,6,3,3,3,3,2,2,2,2,4,4,4,4,
/*0xB0*/ 2,5,2,5,4,4,4,4,2,4,2,4,4,4,4,4,
/*0xC0*/ 2,6,2,8,3,3,5,5,2,2,2,2,4,4,6,6,
/*0xD0*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0xE0*/ 2,6,3,8,3,3,5,5,2,2,2,2,4,4,6,6,
/*0xF0*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
};