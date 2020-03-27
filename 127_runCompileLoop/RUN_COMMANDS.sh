#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''

FILENAME=main.cpp
readarray -t lines <<< "$(md5sum $FILENAME)"
previous_CS=0
current_CS=${lines[0]%% *}
while [ 1 ]
do
	readarray -t lines <<< "$(md5sum $FILENAME)"
	current_CS=${lines[0]%% *}
	if [ $previous_CS == $current_CS ];
	then
		sleep 0.1
	else
		touch a.out && rm -f a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $FILENAME $LIBS && ./a.out && rm a.out
		previous_CS=$current_CS
	fi
done
