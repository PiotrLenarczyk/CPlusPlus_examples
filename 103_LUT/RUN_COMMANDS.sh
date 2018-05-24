#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch consts.cpp; rm consts.cpp; echo "01,127,-22," > consts.cpp
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS LUT.cpp $LIBS && ./a.out
rm a.out consts.cpp
