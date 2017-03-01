#!/bin/bash
#also one can run: 
#qmake && make && ./a.out
qmake
make -j `nproc`
make clean
clear 
./a.out
