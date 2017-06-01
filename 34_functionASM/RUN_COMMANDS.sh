#!/bin/bash
touch a.out && rm a.out 
nasm -f elf64 asm.asm -o asm.o && g++ -c asmFun.cpp && g++ asm.o asmFun.o -o a.out && clear && ./a.out
#rm *.o *.out

