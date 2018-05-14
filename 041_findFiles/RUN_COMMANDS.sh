#!/bin/bash

touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
g++ findFiles.cpp $GCC_FLAGS -I /usr/include -o a.out && clear && ./a.out && touch a.out && rm a.out
