#!/bin/bash
touch a.out && rm a.out
file1D=fileName1D.txt;file4D=fileName4D.txt; file2D=fileNameNestedVec.txt;
touch $file1D $file2D $file4D && rm $file1D $file2D $file4D && g++ -std=c++11 -march=native -O3 saveLoad.cpp -o a.out && clear && ./a.out && rm a.out
touch $file1D $file2D $file4D && rm $file1D $file2D $file4D