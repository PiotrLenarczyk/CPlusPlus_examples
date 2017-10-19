#!/bin/bash
clear
GCC_FLAGS='-std=c++11 -pthread'
touch a.out && rm a.out && g++ backward.cpp $GCC_FLAGS -o a.out 
GCC_FLAGS='-std=c++11 -pthread -mtune=native -march=native -O3'
touch aO.out && rm aO.out && g++ backward.cpp $GCC_FLAGS -o aO.out

echo "===="; echo "Not optimized run: ";
./a.out && rm a.out
echo "===="; echo "Aggresively optimized run: ";
./aO.out && rm aO.out
echo "====";
