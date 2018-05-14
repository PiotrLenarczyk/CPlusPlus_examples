#!/bin/bash
GCC_FLAGS='-mtune=native -march=native -std=c++11 -O3'
PKG_NAME="libreadline-dev"; IS_PKG_INSTALLED=$(dpkg-query -W -f='${Status}' $PKG_NAME 2>/dev/null | grep -c "ok installed")
if (( $IS_PKG_INSTALLED == 0 )); then echo "$PKG_NAME is not installed! Trying to install..."; sudo apt-get install $PKG_NAME; fi
touch a.out && rm a.out && clear && g++ autocompletion.cpp $GCC_FLAGS -lreadline -o a.out && ./a.out 
touch a.out && rm a.out
