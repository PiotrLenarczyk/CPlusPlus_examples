#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm -f a.out data.bin && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT importExport.cpp $LIBS && ./a.out && 
hexdump -Cv -n 32 data.bin
rm a.out 
