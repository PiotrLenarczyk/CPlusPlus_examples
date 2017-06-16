#!/bin/bash

touch a.out && rm a.out
g++ findFiles.cpp -std=c++14 -I /usr/include -o a.out && clear && ./a.out
