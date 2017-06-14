#!/bin/bash

touch a.out && rm a.out
g++ timings.cpp -std=c++11 -o a.out && clear && for (( i=0;i<50;i++ ));do ./a.out; done
