#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++14 -O3 -lpthread'
touch a.out && rm a.out && clear && g++ coutMutex.cpp $GCC_FLAGS -o a.out && ./a.out 
rm a.out
