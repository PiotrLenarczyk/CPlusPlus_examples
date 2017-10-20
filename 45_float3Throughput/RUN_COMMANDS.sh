#!/bin/bash
touch a.out && rm a.out
g++ cachable.cpp -std=c++11 -O3 -o a.out && clear && for (( i = 0; i < 5; i++ )); do ./a.out; echo""; done; rm a.out
