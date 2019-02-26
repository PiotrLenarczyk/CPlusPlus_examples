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
if [ ! -f "tags" ];then 		CHECK_INSTALL "exuberant-ctags"; fi
if [ ! -f "cscope.out" ];then 	CHECK_INSTALL "cscope"; fi
GCC_OPT='-mtune=native -march=native -std=c++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''

cscope -R -b -k #more advanced stuff, integratable with vim
ctags -R		#basic stuff


touch a.out && rm a.out && clear && g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT empty.cpp $LIBS && ./a.out
rm a.out
