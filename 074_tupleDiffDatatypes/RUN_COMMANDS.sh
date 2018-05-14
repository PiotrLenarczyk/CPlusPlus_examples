#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe'
touch a.out && rm a.out && clear && g++ $GCC_FLAGS -o a.out diffDatatypes.cpp && ./a.out 
rm a.out
