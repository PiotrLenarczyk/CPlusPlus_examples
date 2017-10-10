#!/bin/bash
clear && g++ arrayPointers.c -o a.out && echo "====" && echo "Array program executes: " && ./a.out && echo "===="
rm a.out
g++ vecPointers.c -o a.out && echo "Vector program executes: " && ./a.out && echo "===="
rm a.out
