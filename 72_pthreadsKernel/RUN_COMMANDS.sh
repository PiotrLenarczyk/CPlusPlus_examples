#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
LIBS='-pthread'
touch a.out && rm a.out && clear && g++ thKernel.cpp $GCC_FLAGS $LIBS -o a.out && ./a.out 
rm a.out
