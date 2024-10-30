#!/bin/bash

mkdir -p build 
cd build
cmake .. -DPST=True
make
cd ..
./build/Pst 
