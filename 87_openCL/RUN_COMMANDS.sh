#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
INCLUDE=`pkg-config --cflags --libs opencv`
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS trivial.cpp $INCLUDE $LIBS && ./a.out lena.jpg
rm a.out
