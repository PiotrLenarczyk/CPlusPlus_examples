#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out constRef.cpp $GCC_FLAGS $LIBS && ./a.out 
rm a.out
