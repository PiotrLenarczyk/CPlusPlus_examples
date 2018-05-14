#!/bin/bash
touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
g++ cachable.cpp $GCC_FLAGS -o a.out && clear && for (( i = 0; i < 5; i++ )); do ./a.out; echo""; done; rm a.out
