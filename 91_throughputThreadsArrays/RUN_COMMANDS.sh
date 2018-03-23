#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe';
GCC_FLAGS='-fmax-errors=3'
LIBS='-pthread'
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS thArr.cpp $LIBS && ./a.out 
rm a.out
