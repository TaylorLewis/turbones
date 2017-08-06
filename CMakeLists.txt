cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)

set(EXECUTABLE_NAME "turbones")
project(turbones)

if(NOT CMAKE_BUILD_TYPE) # If build type isn't already specified
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Release, Debug."
        FORCE)
endif()

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")

# Add project files
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCE_FILES src/APU.cpp
                 src/Cartridge.cpp
                 src/CPU.cpp
                 src/Emulator.cpp
                 src/main.cpp
                 src/Mapper0.cpp
                 src/Memory.cpp
                 src/NES.cpp
                 src/PPU.cpp
                 include/APU.hpp
                 include/Cartridge.hpp
                 include/CPU.hpp
                 include/Emulator.hpp
                 include/Mapper0.hpp
                 include/Memory.hpp
                 include/NES.hpp
                 include/Opcodes.hpp
                 include/PPU.hpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Add SFML
set(SFML_ROOT CACHE PATH "Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).\nSFML_INCLUDE_DIR will also be inferred from this.")
find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy dll files to target directory, if the current OS is Windows
if (WIN32)
    add_custom_command(
        TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SFML_ROOT}/bin/openal32.dll
                ${SFML_ROOT}/bin/sfml-audio-2.dll
                ${SFML_ROOT}/bin/sfml-graphics-2.dll
                ${SFML_ROOT}/bin/sfml-system-2.dll
                ${SFML_ROOT}/bin/sfml-window-2.dll
                $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>)
endif()