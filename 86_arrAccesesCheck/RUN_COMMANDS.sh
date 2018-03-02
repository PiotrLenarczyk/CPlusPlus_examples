#!/bin/bash
LIBS=''
clear
echo "====";echo "WITHOUT OPTIMISATIONS"; echo "===="
GCC_FLAGS='-mtune=native -march=native -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
echo "====";echo "-O1"; echo "===="
GCC_FLAGS='-mtune=native -march=native -O1 -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
echo "====";echo "-O2"; echo "===="
GCC_FLAGS='-mtune=native -march=native -O2 -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
echo "====";echo "-O3"; echo "===="
GCC_FLAGS='-mtune=native -march=native -O3 -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
echo "====";echo "-Ofast"; echo "===="
GCC_FLAGS='-mtune=native -march=native -Ofast -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
echo "====";echo "-Os"; echo "===="
GCC_FLAGS='-mtune=native -march=native -Os -std=c++11 -pipe';
touch a.out && rm a.out && g++ -o a.out $GCC_FLAGS arrAcc.cpp $LIBS && ./a.out 
touch a.out && rm a.out

