#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
LIBS='-lpthread'
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS asynchro.cpp $LIBS&& ./a.out 
rm a.out
