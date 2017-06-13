#!/bin/bash

touch a.out && rm a.out
g++ randFilenames.cpp -std=c++11 -o a.out && clear && ./a.out
