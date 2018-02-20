#!/bin/bash
touch a.out && rm a.out
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
touch a.out && rm a.out && clear && g++ -o a.out $GCC_FLAGS shVar.cpp
( `find /usr -type f -name 'nvcc'` -arch=sm_50 shVarChild.cpp -o aChild.out && echo "nvcc:" ) || ( g++ $GCC_FLAGS shVarChild.cpp -o aChild.out && echo "gcc:" ) #note quite portable way to compute on GPGPU
./a.out && ./aChild.out
rm a.out aChild.out
