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

fltk/fluid/fluid
