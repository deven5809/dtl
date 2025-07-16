#!/bin/bash

# Check to see if the build directory exists and enter it.
if [ ! -d "out" ]; then
    mkdir out
fi
cd out/cache/test
./unit_tests

