#!/bin/bash
touch a.out && rm a.out
file1D=fileName1D.txt;file4D=fileName4D.txt; file2D=fileNameNestedVec.txt;
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
touch $file1D $file2D $file4D && rm $file1D $file2D $file4D && g++ $GCC_FLAGS saveLoad.cpp -o a.out && clear && ./a.out && rm a.out
touch $file1D $file2D $file4D && rm $file1D $file2D $file4D
