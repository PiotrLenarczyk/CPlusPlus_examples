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


FLTK_INC_PATH=`find . -name 'Fl.H'`
FLTK_INC_PATH=${FLTK_INC_PATH%Fl.*}
FLTK_LIB_PATH=`find . -name 'libfltk.a'`
FLTK_LIB_PATH=${FLTK_LIB_PATH%lib*}
X11_LIBS='-lX11 -lXext -lXfixes'
INCS='-Ifltk/'
LIBS="-L${FLTK_LIB_PATH} -lfltk -ldl ${X11_LIBS}"

FILE=cross_fltk.cpp

compile()
{	touch a.out && rm -f a.out && clear 						&&
	g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $1 $LIBS $INCS	&&
	./a.out														&&
	rm -f a.out
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
#compile $FILE
