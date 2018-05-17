#!/bin/bash
GCC_OPT='-mtune=native -march=native -Ofast -pipe'
GCC_FLAGS='-fmax-errors=3 -nostartfiles'
LIBS=''
touch a.out && rm a.out && clear
	gcc 											\
		-o a.out $GCC_OPT $GCC_FLAGS noMain.c $LIBS 
printf "ProgRun:\n====\n";./a.out;echo "====";
rm a.out
