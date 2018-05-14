#!/bin/bash
clear && touch a.out aFlags.out avx.out avxFlags.out  && rm *.out
echo "==============================" && echo "no compiler optimalization" && echo "=============================="  && g++ -std=c++11 -O3 stlContainers.cpp -o aFlags.out && g++ -std=c++11 stlContainers.cpp -o a.out && ./a.out && echo "==============================" && echo "compiler Flags execution" && echo "==============================" && ./aFlags.out
echo "==============================" && echo "Yifei AVX no compiler optimalization" && echo "==============================" && g++ -O3 -mavx avxMatrix.cpp -o avxFlags.out && g++ -mavx avxMatrix.cpp -o avx.out && ./avx.out && echo "==============================" && echo "Yifei AVX compiler Flags execution" && echo "==============================" && ./avxFlags.out
rm *.out
