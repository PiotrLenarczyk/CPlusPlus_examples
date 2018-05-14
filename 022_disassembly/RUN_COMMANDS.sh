#!/bin/bash
#also one can run: 
#qmake && make && ./a.out
rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS addDisassembly.cpp
clear 
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
readelf -dV a.out
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo "Program Output:"
echo "======================="
./a.out
echo "======================="
rm a.out
