#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS dynamicArrays.cpp $LIBS && ./a.out 
rm a.out
