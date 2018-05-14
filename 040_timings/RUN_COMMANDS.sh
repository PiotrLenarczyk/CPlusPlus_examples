#!/bin/bash

touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
g++ timings.cpp $GCC_FLAGS -o a.out && clear && for (( i=0;i<50;i++ ));do ./a.out; done
