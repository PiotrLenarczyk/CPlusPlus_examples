#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS saveToFile.cpp && ./a.out 
rm a.out
