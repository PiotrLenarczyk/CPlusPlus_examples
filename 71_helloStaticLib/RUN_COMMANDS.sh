#!/bin/bash
#https://ryanstutorials.net/bash-scripting-tutorial/bash-functions.php
findDeleteRecursively()
{	find `pwd` -name '*.o' -exec rm -rf {} \; 		&& 
	find `pwd` -name '*.out' -exec rm -rf {} \;		&&
	find `pwd` -name '*.a' -exec rm -rf {} \;		
};

GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3 -g'
OBJ_FLAGS='-c -static'
findDeleteRecursively;

####
# LIB compile
####
	cd libStuff/ &&	g++ $GCC_FLAGS $OBJ_FLAGS helloLib.cpp -o ../helloLib.o && cd .. &&
	ar crs libhello.a helloLib.o			&&
	echo "lib demangle:"				    &&
	nm -C libhello.a					    &&
	
####
# Main prog compile
####
g++ $GCC_FLAGS $OBJ_FLAGS empty.cpp -L. -lhello -o empty.o &&

####
# Link object files
####
g++ $GCC_FLAGS -v helloLib.o empty.o -o a.out &&
touch a.out && ./a.out	&&
gdb -tui a.out  &&



findDeleteRecursively;
