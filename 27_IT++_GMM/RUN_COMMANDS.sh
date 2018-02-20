#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
LIBS='-litpp'
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS GMM_ex1.cpp $LIBS&& ./a.out 
rm a.out
