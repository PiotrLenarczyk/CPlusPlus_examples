#!/bin/bash
#LOAD DATA FROM CLIENT TO LISTENING SERVER
touch server client && rm server client && g++ serverShMem.cpp -o server && g++ client.c -o client 
./server 5601
#additional terminal command: #./client localhost 5601
