#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
clear && g++ $GCC_FLAGS arrayPointers.c -o a.out && echo "====" && echo "Array program executes: " && ./a.out && echo "===="
rm a.out
g++ vecPointers.c -o a.out && echo "Vector program executes: " && ./a.out && echo "===="
rm a.out
