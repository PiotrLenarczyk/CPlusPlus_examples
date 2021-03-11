#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
#check whether fltk exists in the system, if not get repo
if [[ ! -d "fltk" ]]
then
	git clone https://github.com/fltk/fltk.git
	cd fltk/
	make -j `nproc`
	./configure -disable-xft
	make -j`nproc`
	cd ..
fi


PROG=00_hello

fltk/fluid/fluid -c ${FILE%.*}.fl
FILE=${PROG}.cxx
compile()
{	rm -f ${1%.*} ${1%.*}.o && clear							&&
	make ${1%.*}												&&
	./${1%.*}													&&
	rm -f ${1%.*} ${1%.*}.o
};

compile_loop()
{	old_CS=0
	new_CS=( $( md5sum $1 ) )
	while [ 0 -lt 1 ]
	do
		if [ $old_CS[0] != $new_CS[0] ]
		then
			old_CS=$new_CS										&&
#			clear												&&
			compile $1											
		fi
		sleep 0.1
		new_CS=( $( md5sum $1 ) )
	done
};

compile_loop $FILE
