#!/bin/bash

# Check to see if the build directory exists and enter it.
if [ ! -d "out" ]; then
    mkdir out
fi
cd out

# Run CMake to generate a build system. We also want it to output a compile
# commands json file for VS Code to parse.
cmake ../ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Perform the build.
cmake --build .