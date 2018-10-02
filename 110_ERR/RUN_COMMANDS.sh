#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -O0 -pipe'
GCC_FLAGS='-fmax-errors=3 -g'
LIBS=''
touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS empty.cpp $LIBS &&  lxterminal -t "GDB" -e "gdb a.out -ex \"tui enable\" -ex \"file a.out\""
#rm a.out
