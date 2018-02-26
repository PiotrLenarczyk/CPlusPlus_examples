#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -Ofast -pipe';
touch a1.out && rm a1.out && clear && g++ -o a1.out $GCC_FLAGS constPtr.cpp
GCC_FLAGS='-std=c++11 -pipe';
touch a2.out && rm a2.out && clear && g++ -o a2.out $GCC_FLAGS constPtr.cpp
echo "====";echo "Optimized run:";echo "===="
./a1.out
echo "====";echo "Non-optimized run:";echo "===="
./a2.out 
rm a1.out a2.out
