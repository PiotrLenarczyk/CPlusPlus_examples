#!/bin/bash
touch a.out && rm a.out
g++ -std=c++11 -O3 saveVecD.cpp -o a.out && clear && ./a.out
