#pragma once

#include <string>

class Emulator {
public:
    Emulator();
    void run();

    std::string rom_path;

private:
    // Attempts to load file. Accepts iNES files (typically denoted .nes in the file extension).
    void loadROM(const std::string rom_path);

};