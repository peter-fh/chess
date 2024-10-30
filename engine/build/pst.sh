#!/bin/bash

mkdir -p cmake 
cd cmake
cmake .. -DPST=True
make
cd ..
./build/Pst 
