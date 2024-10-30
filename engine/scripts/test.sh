#!/bin/bash

mkdir -p build
cd build
cmake .. -DTEST=True
make
cd ..
./build/Test 
