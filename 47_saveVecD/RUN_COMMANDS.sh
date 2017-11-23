#!/bin/bash
touch a.out && rm a.out
g++ -std=c++11 -march=native -O3 saveVecD.cpp -o a.out && clear && ./a.out #&& rm tmp.txt a.out
