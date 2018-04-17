#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe';
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS setBit.cpp $LIBS && ./a.out 
rm a.out
