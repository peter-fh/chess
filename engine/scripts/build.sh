#!/bin/bash

mkdir -p build 
cd build 
cmake .. -DENGINE=True
make
cd ..
./build/Engine 
