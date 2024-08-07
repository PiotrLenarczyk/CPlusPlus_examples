#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''

FILE=redir_stdouerr.cpp

compile()
{	touch a.out && rm -f a.out && clear 						&& 
	g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS 		&&
	xterm -geometry 83x31+0+850 -hold -e "tail -F stdout.txt" &	
	xterm -geometry 83x31+510+850 -hold -e "tail -F stderr.txt" &	
	./a.out														&&
	rm a.out
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

compile_loop $FILE
