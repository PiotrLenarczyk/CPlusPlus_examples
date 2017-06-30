#!/bin/bash
clear
g++ dummyLoad.cpp -o dummyLoad.out
./dummyLoad.out & 
./dummyLoad.out & 
./dummyLoad.out & 
exec bash

g++ -std=c++11 -O3 threadsPerCore.cpp  -lpthread -o a.out && clear && ./a.out
# kill $(ps aux | grep './dummyLoad' | awk '{print $2}')        #to stop dummy load run this!
touch dummyLoad.out a.out
