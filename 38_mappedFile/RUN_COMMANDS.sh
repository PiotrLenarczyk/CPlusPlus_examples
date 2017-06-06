#!/bin/bash
touch a.out && rm a.out
qmake && make -j`nproc` && make clean && clear && ./a.out a.txt
# rm a.out
