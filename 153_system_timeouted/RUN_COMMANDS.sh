#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS='-lpthread'

FILE=systemt.cpp

compile()
{	touch a.out && rm -f a.out && clear 						&& 
	g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS 		&& 
	./a.out														&&
	kill -9 `pidof a.out` &>> /dev/null  						
	touch a.out && rm -f a.out
};

compile_loop()
{	old_CS=0
	new_CS=( $( md5sum $1 ) )
	while [ 0 -lt 1 ]
	do
		if [ $old_CS[0] != $new_CS[0] ]
		then
			old_CS=$new_CS										&&
			clear												&&
			compile $1											
		fi
		sleep 0.1
		new_CS=( $( md5sum $1 ) )
	done
};

xterm -geometry 83x31+0+850 -hold -e "watch -n 0 cat /tmp/systemt_stdout.txt" &	
xterm -geometry 83x31+510+850 -hold -e "watch -n 0 cat /tmp/systemt_stderr.txt" &
compile_loop $FILE
