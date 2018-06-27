#!/bin/bash
GCC_OPT='-mtune=native -march=native -O0 -pipe'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm a.out && clear && gcc -o a.out $GCC_OPT $GCC_FLAGS strFind.cpp $LIBS && ./a.out 77771001 123
rm a.out
