#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3 -g'
touch a.out && rm a.out && clear && g++ funcPtr.cpp $GCC_FLAGS -o a.out && ./a.out #&& touch a.out && rm a.out
