# TurboNES

This is a NES emulator, written for learning, fun, and because it's cool as hell! Also, by the time this project is complete, I want this to be one of the more clear and better documented emulators, to be a helpful example for anyone else learning to write an emulator.

## Building

This project requires **[SFML](https://www.sfml-dev.org/)**, and uses **[CMake](https://cmake.org/)** to build. A **C++11** compliant compiler is also required to build.

### Windows

*This example uses Visual Studio.*

1. Install **[CMake](https://cmake.org/download/)**.
2. Download **[SFML](https://www.sfml-dev.org/download.php)**, and place directory wherever *(there's no standard installation directory for SFML in Windows)*.
3. Open **Command Prompt**, and type the following commands in it.
4. If **[Git](https://git-scm.com/download/win)** is installed, simply type: `git clone https://github.com/TaylorLewis/turbones`. Otherwise download this repository in GitHub, unzip files, and direct the Command Prompt to the repository folder with `cd`.
5. `mkdir build`
6. `cd build`
7. `cmake .. -DSFML_ROOT=<sfml-path>`, where *\<sfml-path>* is the path to your SFML directory.
8. `turbones.sln`

This will open the project in Visual Studio. Then:

9. Make sure _**Release**_ is selected (under the menu bar), rather than _**Debug**_.
10. Press Ctrl+Shift+B to build the solution, or in the menu bar click *Build > Build Solution*.


### macOS

1. Open the **Terminal**, and type the following commands:
2. If you don't have a package manager installed, like **[Homebrew](https://brew.sh/)**, type:
`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
3. `brew install cmake sfml`
4. `git clone https://github.com/TaylorLewis/turbones`
5. `mkdir build`
6. `cd build`
7. `cmake ..`
8. `make`

### Linux

In the terminal, type:

1. `sudo apt-get install cmake libsfml-dev`
2. `git clone https://github.com/TaylorLewis/turbones`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make`

## Usage


`turbones [options]... <path-to-rom-file>`
    
Example : `turbones roms/Zelda.nes`

## Legal

This project is licensed under the terms of the [MIT license](https://tldrlegal.com/license/mit-license).

Laws vary across countries, but basically, in the United States:
* Emulators are legal.
* Personal backups of games you own are quite probably legal.
* The acquisition of illegally distributed games that you own could possibly be legal.
* The unauthorized distribution of copyrighted games is not legal.

See Wikipedia for [more information](https://en.wikipedia.org/wiki/Video_game_console_emulator#Legal_issues).

## References

There is much information on the NES throughout the internet, but unfortunately, no one source is entirely adequate on its own. Thus to fully understand the console, one must consume a number of sources.

### Specification

* [NES Reference Guide - Nesdev Wiki](http://wiki.nesdev.com/w/index.php/NES_reference_guide). The most useful and thorough reference.
* [Nintendo Entertainment System Documentation](http://nesdev.com/NESDoc.pdf). A good overview of the console.
* [6502 Introduction](http://www.obelisk.me.uk/6502/index.html). Particularly useful for its clean, detailed specification of opcode behavior.

### Videos

* [How Oldschool Graphics Worked Part 1 - Commodore and Nintendo](https://youtu.be/Tfh0ytz8S0k)
* [How Oldschool Sound/Music Worked](https://youtu.be/q_3d1x2VPxk)
* [How Oldschool ROM Cartridge Games Worked](https://youtu.be/NLEMsw1SjDY)