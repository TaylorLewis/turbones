#include "PPU.hpp"

void PPU::powerOn() {

}

void PPU::step() {
    ++cycle;

    if (cycle >= 341) { // scanline done
        ++scanline;
        cycle = 0;

        if (scanline >= 262) { // frame done
            scanline = 0;
            odd_frame ^= 1;
        }
    }


}

uint8_t PPU::readRegister(const uint16_t& address) {
    switch (address) {
        case 0x2002:
            //return readStatus();
            break;
        case 0x2004:
            //return readOAMData();
            break;
        case 0x2007:
            //return readData();
            break;
        default:
            // TODO: ERROR
            break;
    }


    return 0; // d
}

void PPU::writeRegister(const uint16_t& address, const uint8_t& value) {
    switch (address) {
        case 0x2000:
            //writeControl(value);
            break;
        case 0x2001:
            //writeMask(value);
            break;
        case 0x2003:
            //writeOAMAddress(value);
            break;
        case 0x2004:
            //writeOAMData(value);
            break;
        case 0x2005:
            //writeScroll(value);
            break;
        case 0x2006:
            //writeAddress(value);
            break;
        case 0x2007:
            //writeData(value);
            break;
        case 0x4014:
            //writeDMA(value);
            break;
        default:
            // TODO: ERROR
            break;
    }
}



void PPU::writeData(const uint8_t& value) {
    vram_address = value;

    if (ppuctrl_increment == 0) {
        vram_address += 1; }
    else {
        vram_address += 32; }
}