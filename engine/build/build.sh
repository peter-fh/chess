#!/bin/bash

mkdir -p cmake 
cd cmake 
cmake .. -DENGINE=True
make
cd ..
./build/Engine 
