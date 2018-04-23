#!/bin/bash
GCC='-mtune=native -march=native -std=c++11 -pipe'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm a.out && clear
N=1
g++ -o a.out $GCC_OPT $GCC_FLAGS -O0 loops.cpp $LIBS && echo "====";echo "-O0";echo "====";for((i=0;i<N;i++));do ./a.out;done
g++ -o a.out $GCC_OPT $GCC_FLAGS -Ofast loops.cpp $LIBS && echo "====";echo "-Ofast";echo "====";for((i=0;i<N;i++));do ./a.out;done
rm a.out
