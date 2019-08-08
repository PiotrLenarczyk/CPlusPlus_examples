#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3 -Wno-write-strings'
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT strToChars.cpp $LIBS && ./a.out
rm a.out
