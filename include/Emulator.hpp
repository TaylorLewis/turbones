#pragma once

#include <string>

class Emulator {
public:
    Emulator();
    void run();

    std::string rom_path;

private:
    void loadROM(const std::string rom_path);

};