#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
PROG_FLAGS='-DSELF_CONTAINED'
touch a.out && rm -f a.out data.bin && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $PROG_FLAGS importExport.cpp $LIBS && ./a.out && 
echo "====" && hexdump -Cv -n 64 -s 0x0 data.bin
echo "====" && hexdump -Cv -n 32 -s 0x3000 data.bin
rm a.out 
