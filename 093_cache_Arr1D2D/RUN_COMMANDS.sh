#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe';
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS arr1D2D.cpp $LIBS && ./a.out 
sudo perf stat -B -e cache-references,cache-misses -r 5 ./a.out
rm a.out
