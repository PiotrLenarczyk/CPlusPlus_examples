#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
clear && g++ $GCC_FLAGS loopUnroll.cpp -o a.out && ./a.out
rm a.out

