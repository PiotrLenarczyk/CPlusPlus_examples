#!/bin/bash
touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
g++ vectorMedian.cpp $GCC_FLAGS -o a.out && clear && ./a.out
