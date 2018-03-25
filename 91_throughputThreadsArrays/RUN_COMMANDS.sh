#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -pipe';
GCC_FLAGS='-fmax-errors=3 -fpermissive'
LIBS='-pthread'
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS thArr.cpp $LIBS && for ((i=0;i<5;i++)); do ./a.out;done;
rm a.out
