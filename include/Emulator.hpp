#pragma once

#include <string>

#include <NES.hpp>

class Emulator {
public:
    void run();

    std::string rom_path;

private:
    NES nes;

};