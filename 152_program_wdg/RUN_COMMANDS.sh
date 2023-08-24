#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''

FILE=soft_wdg.cpp
FILE_SOFTWARE=software.cpp

compile_software()
{	touch software.out && rm -f software.out && clear 					&& 
	g++ -o software.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS 		&& 
	./software.out	&													
};

compile()
{	touch soft_wdg.out && rm -f soft_wdg.out && clear 					&& 
	g++ -o soft_wdg.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS 		&& 
	./soft_wdg.out	software.out 500											
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

compile_software $FILE_SOFTWARE

compile_loop $FILE
