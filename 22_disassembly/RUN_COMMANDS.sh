#!/bin/bash
#also one can run: 
#qmake && make && ./a.out
rm a.out
qmake
make -j `nproc`
make clean
clear 
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
readelf -d -V a.out
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo "Program Output:"
echo "======================="
./a.out
echo "======================="
rm a.out Makefile
