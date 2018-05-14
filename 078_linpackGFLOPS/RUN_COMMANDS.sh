#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -Ofast -pipe';
touch a.out && rm a.out && clear 
gcc -o a.out -DSINGLE_PREC $GCC_FLAGS linpack.c && ./a.out && rm a.out
echo "================================================================="
echo "================================================================="
echo "================================================================="
gcc -o a.out -DDOUBLE_PREC $GCC_FLAGS linpack.c && ./a.out && rm a.out
