#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe'
touch a.out && rm a.out && clear && g++ diffDatatypes.cpp $GCC_FLAGS -o a.out && ./a.out 
rm a.out
