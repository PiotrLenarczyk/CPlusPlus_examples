#!/bin/bash
touch a.out && rm a.out
qmake && make -j`nproc` && make clean && ( `find /usr -type f -name 'nvcc'` -arch=sm_50 shVarChild.cpp -o aChild.out && echo "nvcc:" ) || ( g++ -O2 shVarChild.cpp -o aChild.out && echo "gcc:" ) #note quite portable way to compute on GPGPU
./a.out && ./aChild.out

