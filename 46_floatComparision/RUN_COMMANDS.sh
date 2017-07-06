#!/bin/bash
touch a.out && rm a.out
g++ floatComparision.cpp -O3 -std=c++11 -o a.out && clear && ./a.out
