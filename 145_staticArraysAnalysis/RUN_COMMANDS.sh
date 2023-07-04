#!/bin/bash
GCC_OPT='-g -O0'
GCC_FLOAT=''
GCC_FLAGS=''
LIBS=''

FILE=analyze.c

check_install_package()
{
	PKG_NAME=$1 
	IS_PKG_INSTALLED=$(dpkg-query -W -f='${Status}' $1 2>/dev/null | grep -c "ok installed")
	if (( $IS_PKG_INSTALLED == 0 )); 
		then echo "$PKG_NAME is not installed! Trying to install..."; 
		sudo apt-get install $PKG_NAME; 
	fi
};

compile()
{	touch a.out && rm -f a.out && clear 						&& 
	gcc -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS 		&& 
	./a.out														
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


check_install_package cppcheck
check_install_package splint
#compile_loop $FILE
#compile $FILE
cppcheck $FILE
splint $FILE
