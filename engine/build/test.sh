#!/bin/bash

mkdir -p cmake
cd cmake
cmake .. -DTEST=True
make
cd ..
./build/Test 
