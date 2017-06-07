#!/bin/bash
touch aRead.out aWrite.out && rm aRead.out aWrite.out
g++ mmappedRead.cpp -o ./aRead.out  && ./aRead.out fileToMemory.txt
g++ mmapedWrite.cpp -o aWrite.out && ./aWrite.out memoryToFile.txt && echo "content of memoryToFile.txt: " && cat memoryToFile.txt
# rm aRead.out aWrite.out
