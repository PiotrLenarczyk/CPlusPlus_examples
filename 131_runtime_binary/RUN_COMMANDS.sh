#!/bin/bash
clear
GCC_OPT='-mtune=native -march=native -O0 -pipe -g'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''

#compilation of input binary
gcc main.c 
BINARY_FILE=a.out
MODIFIED_OUT=b.out

old_parse_CS=0
old_variables_CS=0
old_modify_CS=0
new_parse_CS=( $( md5sum parse.c ) )
new_variables_CS=( $( md5sum variables.h ) )
new_modify_CS=( $( md5sum modify_runtime_binary.c ) )
while [ 0 -lt 1 ]
do
	if [ $old_parse_CS[0] != $new_parse_CS[0] ]
	then
		clear
		touch parse.out && rm -f parse.out && gcc -o parse.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT parse.c $LIBS
		sleep 0.1
		./parse.out							&&
		echo -e "\n===="					&&
		./modify_binary.out ${BINARY_FILE} ${MODIFIED_OUT}
		old_parse_CS=$new_parse_CS;
	fi
	if [ $old_modify_CS[0] != $new_modify_CS[0] ]
	then
		clear
		touch modify_binary.out && rm -f modify_binary.out && gcc -o modify_binary.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT modify_runtime_binary.c $LIBS
		sleep 0.1
		./parse.out							&&
		echo -e "\n===="					&&
		./modify_binary.out ${BINARY_FILE} ${MODIFIED_OUT}
		old_modify_CS=$new_modify_CS;
	fi
	if [ $old_variables_CS[0] != $new_variables_CS[0] ]
	then
		clear
		touch parse.out && rm -f parse.out && gcc -o parse.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT parse.c $LIBS
		touch modify_binary.out && rm -f modify_binary.out && gcc -o modify_binary.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT modify_runtime_binary.c $LIBS
		./parse.out							&&
		echo -e "\n===="					&&
		./modify_binary.out ${BINARY_FILE} ${MODIFIED_OUT}
		sleep 0.2
		old_variables_CS=$new_variables_CS;
	fi
	sleep 0.1
	new_parse_CS=( $( md5sum parse.c ) )
	new_variables_CS=( $( md5sum variables.h ) )
	new_modify_CS=( $( md5sum modify_runtime_binary.c ) )
done

#./binary.out
#./modify_binary.out
