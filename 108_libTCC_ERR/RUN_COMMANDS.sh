#!/bin/bash
CHECK_INSTALL()
{	PKG_NAME=$1; PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $PKG_NAME|grep "install ok installed")
	if [ "" == "$PKG_OK" ]; then
		echo "No [$PKG_NAME]. Setting up [$PKG_NAME]."
		sudo apt-get --force-yes --yes install $PKG_NAME
	else
		echo "[$PKG_NAME] : installed"
	fi
};
CHECK_INSTALL "tcc" 
CHECK_INSTALL "libtcc-dev"
CHECK_INSTALL "libx11-dev"

#=====
GCC_OPT='-mtune=native -march=native -Ofast -pipe'
GCC_FLAGS='-fmax-errors=3'
INC='-I/usr/local/lib/tcc/include'
LIBS='-ltcc -ldl'
touch a.out && rm a.out && clear && gcc -o a.out $GCC_OPT $GCC_FLAGS empty.c $INC $LIBS && ./a.out externProg.c
rm a.out
