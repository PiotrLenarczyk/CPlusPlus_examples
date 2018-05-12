#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Os -pipe'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
touch a.out && rm a.out && clear 
echo "================================================================";
echo "preprocessed foo():";
echo "================================================================";
g++ -o func.o -E $GCC_OPT $GCC_FLAGS func.cpp $LIBS
cat func.o
echo "================================================================";
echo "compiled foo():";
echo "================================================================";
g++ -o func.o -S $GCC_OPT $GCC_FLAGS func.cpp $LIBS
cat func.o
echo "================================================================";
echo "assembled foo():";
echo "================================================================";
g++ -o func.s -c $GCC_OPT $GCC_FLAGS func.cpp $LIBS
hexdump func.s
echo "================================================================";
echo "run main():"
echo "================================================================";
g++ -o a.out $GCC_OPT $GCC_FLAGS compilation.cpp $LIBS && ./a.out
echo "================================================================";
stat --printf "foo() source size: %s\n" func.cpp 
stat --printf "foo() machineCode size: %s\n" func.s 
echo "================================================================";
rm func.o func.s a.out
