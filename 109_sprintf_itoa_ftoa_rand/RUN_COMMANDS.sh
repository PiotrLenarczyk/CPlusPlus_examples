#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLAGS='-fmax-errors=3 -Wno-write-strings -g'
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS sprintfItoa.cpp $LIBS && 
gdb ./a.out -ex "tui enable" -ex "set pagination off"  -ex "set output-radix 16" -ex "tui enable" -ex "set confirm off" -ex "b main" -ex "r"	&&
rm a.out	&&
exit 0;
