@echo off
rem gcc -O3 -std=c99 -o test_tutti.exe test_tutti.c -lm
gcc -O3 -std=c99 -Wall -Wextra -pedantic -o test_tutti.exe test_tutti.c -lm
test_tutti.exe
start output.wav