#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Cartridge.hpp"

Cartridge::Cartridge(const std::string& rom_path) {
    loadRom(rom_path);
}

void Cartridge::loadRom(const std::string& rom_path) {
    std::ifstream rom(rom_path, std::ios::binary);

    checkStream(rom, rom_path);
    checkFileSize(rom);

    if (header.trainer) {
        loadTrainer(rom); }
    loadPRG(rom);
    loadCHR(rom);



    std::cout << "File loaded." << std::endl;
}

void Cartridge::checkStream(const std::ifstream& rom, const std::string& rom_path) {
    if (rom.fail()) {
        std::cerr
            << "Couldn't load file at designated path: " << rom_path << '\n'
            << "Usage: turbones [options] <path-to-rom-file>" << std::endl;
        throw std::runtime_error("Failed ifstream");
    }

    if (rom.bad()) {
        std::cerr << "Unknown file error." << std::endl;
        throw std::runtime_error("Bad ifstream");
    }
}

void Cartridge::checkFileSize(std::ifstream& rom) {
    // Get length of file
    rom.seekg(0, std::ios::end);
    const std::streampos rom_size = (int)rom.tellg();
    rom.seekg(0, std::ios::beg);

    if (rom_size > MAX_FILE_SIZE) {
        std::cerr
            << "File too large: " << rom_size << " bytes.\n"
            << "Max file size: 1 MB = " << MAX_FILE_SIZE << " bytes." << std::endl;
        throw std::runtime_error("File too large");
    }
}

void Cartridge::loadHeader(std::ifstream& rom) {
    std::array<char, HEADER_SIZE> buffer;
    rom.read(buffer.data(), buffer.size());

    header = Header(buffer); // TODO: Rework.
}

void Cartridge::loadTrainer(std::ifstream& rom) {
    std::array<char, TRAINER_SIZE> buffer;
    rom.read(buffer.data(), buffer.size());

    // TODO
}

void Cartridge::loadPRG(std::ifstream& rom) {
    std::array<char, PRG_PAGE_SIZE> buffer;
    for (int i = 0; i < header.prg_rom_pages; ++i) {
        rom.read(buffer.data(), buffer.size());

        // TODO
    }
}

void Cartridge::loadCHR(std::ifstream& rom) {
    std::array<char, CHR_PAGE_SIZE> buffer;

    for (int i = 0; i < header.chr_rom_pages; ++i) {
        rom.read(buffer.data(), buffer.size());

        // TODO
    }
}



Cartridge::Header::Header() {}

Cartridge::Header::Header(const std::array<char, HEADER_SIZE>& input) {
    checkHeader(input);

    prg_rom_pages = input[4];
    chr_rom_pages = input[5];

    mapper_number = (input[7] & 0xF0) | (input[6] & 0xF0 >> 4);

    mirroring   = input[6] & 0b0000'0001;
    battery     = input[6] & 0b0000'0010 >> 1;
    trainer     = input[6] & 0b0000'0100 >> 2;
    four_screen = input[6] & 0b0000'1000 >> 3;

    vs_unisystem    = input[7] & 0b0000'0001;
    playchoice_10   = input[7] & 0b0000'0010 >> 1;
    nes_2 = (0b10 == (input[7] & 0b0000'1100 >> 2));
}

// The first four bytes of the iNES header are always the same.
void Cartridge::Header::checkHeader(const std::array<char, HEADER_SIZE>& input) {
    if (    input[0] == 0x4E    // N
         && input[1] == 0x45    // E
         && input[2] == 0x53    // S
         && input[3] == 0x1A) { // MS-DOS end-of-file
        return; }
    else {
        std::cerr << "Invalid or unsupported file format." << std::endl;
        throw std::runtime_error("iNES header not found");
    }
}