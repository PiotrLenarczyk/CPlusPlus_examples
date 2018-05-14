#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
touch a.out && rm a.out && clear && g++ getOpt.cpp $GCC_FLAGS -o a.out 
echo "./a.out:"; ./a.out
echo "./a.out -x:";./a.out -x 
echo "./a.out -x -14_-11:"; ./a.out -x -14_-11
rm a.out
