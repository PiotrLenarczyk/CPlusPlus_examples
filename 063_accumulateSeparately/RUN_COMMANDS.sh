#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
touch a.out && rm a.out && clear && g++ acc.cpp $GCC_FLAGS -o a.out && ./a.out 
rm a.out
