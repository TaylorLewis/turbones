#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

#include "Emulator.hpp"

void printHelpMessage() {
    std::cout
        << "A NES emulator. Takes .nes files.\n\n"
        << "Usage: turbones [options] <path-to-rom-file>\n\n"
        << "Options:\n"
        << "\t-h  --help\n"
        << "\t\tPrint this help text and exit."
        << std::endl;
}

void handleArguments(const int& argc, char* argv[], Emulator& emulator) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h"
             || arg == "--help") {
            printHelpMessage();
            exit(EXIT_SUCCESS);
        }
        else if (i == argc - 1) {
            emulator.rom_path = arg;
        }
        else {
            std::cerr << "Unrecognized argument: " << arg << std::endl; }
    }
}

// Prints failure message, and then waits until Enter ('\n') is pressed,
// so there's time for the message to be read, in case the console closes itself immediately afterwards.
// It turns out to be simpler to write this portably, if we wait for Enter, rather than "any key".
void printFailureAndWait(const std::runtime_error& e) {
    std::cerr
        << "\nFailed to run (" << e.what() << "). Shutting down.\n"
        << "Press Enter to exit . . . " << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for enter key.
}

int main(const int argc, char* argv[]) {
    Emulator emulator;
    handleArguments(argc, argv, emulator);

    try {
        emulator.run(); }
    catch (const std::runtime_error& e) {
        printFailureAndWait(e);
        return EXIT_FAILURE;
    }
}