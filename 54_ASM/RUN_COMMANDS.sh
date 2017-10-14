#!/bin/bash
asmFile=$1
nasm -f elf $asmFile -o a.o && ld -m elf_i386 -s -o a.out a.o && ./a.out
rm a.o a.out
