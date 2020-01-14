gcc -g -O0 -std=c99 -no-pie -Wall -Wextra -pedantic -o test_tutti test_tutti.c -lm \
	&& ./test_tutti \
	&& cvlc --play-and-exit output.wav || \
	gdb test_tutti