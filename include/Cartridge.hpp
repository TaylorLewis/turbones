#pragma once

#include <stdint.h>
#include <string>
#include <array>
#include <vector>

// Game cartridge. Takes iNES formatted NES ROMs (iNES is the standard format).
class Cartridge {
public:
    static constexpr int TRAINER_SIZE  =  0x200, // Size of space allocated for trainer. 512 B.
                         PRG_PAGE_SIZE = 0x4000, // Program ROM page size. 16 KB.
                         CHR_PAGE_SIZE = 0x2000; // Character ROM page size.  8 KB.

    Cartridge(const std::string& rom_path);

    // Program data.
    std::vector<uint8_t> prg_rom;
    // Character data, aka pattern tables. Used for graphics.
    std::vector<uint8_t> chr_rom;

private:
    // Sizes in bytes.
    static constexpr int MAX_FILE_SIZE = 0x100000, // Max NES ROM file size accepted. 1 MB.
                                                   // The biggest official NES ROM is 6 Mb.
                         HEADER_SIZE = 0x10; // Size of iNES header. 16 B.

    // Attempts to load file. Accepts iNES files (typically denoted .nes in the file extension).
    void loadRom(const std::string& rom_path);
    // Throws exception if stream's fail or bad bits are set.
    void checkStream(const std::ifstream& rom, const std::string& rom_path);
    // Throws exception if file size is greater than max allowed.
    void checkFileSize(std::ifstream& rom);

    void loadHeader(std::ifstream& rom);
    void loadPRG(std::ifstream& rom);
    void loadCHR(std::ifstream& rom);

    // iNES header data, found in the first 16 bytes of iNES formatted ROMs.
    class Header {
        public:
            // Takes first 16 bytes of loaded ROM file.
            void load(const std::array<uint8_t, HEADER_SIZE>& input);

            uint8_t prg_rom_pages, // Number of 16 KB program ROM pages.
                    chr_rom_pages, // Number of  8 KB character ROM pages (0 indicates CHR RAM).
                    mapper_number;

            bool mirroring, // 0 = horizontal, 1 = vertical.
                 battery, // SRAM at $6000-$7FFF battery backed.
                 trainer, // 512 byte trainer at $7000-$71FF. Used in deprecated ROM dumps and some old ROM hacks.
                 four_screen, // Four screen mirroring mode. When set, 'mirroring' flag has no effect. Very rarely used.
                 vs_unisystem, // VS. System arcade ROM.
                 playchoice_10, // PlayChoice-10 arcade system ROM.
                 nes_2; // NES 2.0 header. The format extends iNES.
            // TODO: Add NES 2.0 extension.
        private:
            // Checks if ROM file begins with an iNES header.
            void checkHeader(const std::array<uint8_t, HEADER_SIZE>& input);
    };

    Header header;
};