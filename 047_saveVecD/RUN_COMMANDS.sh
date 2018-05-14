#!/bin/bash
touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
g++ $GCC_FLAGS saveVecD.cpp -o a.out && clear && ./a.out #&& rm tmp.txt a.out
