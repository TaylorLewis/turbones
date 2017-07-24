#include <iostream>
#include <fstream>

#include "Emulator.hpp"

Emulator::Emulator() {

}

// The first four bytes of the iNES header are always the same.
void checkHeader(char header[]) {
    if (    header[0] == 0x4E  // N
         && header[1] == 0x45  // E
         && header[2] == 0x53  // S
         && header[3] == 0x1A) // MS-DOS end-of-file
        return;
    else {
        std::cerr << "Invalid or unsupported file format. iNES header not found." << std::endl;
        throw std::runtime_error("Invalid file");
    }
}

void Emulator::loadROM(const std::string rom_path) {
    std::ifstream rom(rom_path, std::ios::binary);

    if (rom.fail()) {
        std::cerr
            << "Couldn't load file at designated path: " << rom_path << '\n'
            << "Usage: turbones [OPTION]... [FILE]\n\n" << std::endl;
        throw std::runtime_error("Failed ifstream");
    }

    if (rom.bad()) {
        std::cerr << "Unknown file error." << std::endl;
        throw std::runtime_error("Bad ifstream");
    }



    // Get length of file
    rom.seekg(0, std::ios::end);
    const int rom_size = (int)rom.tellg();
    rom.seekg(0, std::ios::beg);

    // TODO: Check against max file length, whatever that is.

    // The first 16 bytes of an iNES file is the iNES header.
    char header[16];
    rom.read(header, rom_size);

    void checkHeader();



    std::cout << "File loaded." << std::endl;
}

void Emulator::run() {
    loadROM(rom_path);


}