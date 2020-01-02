gcc -g -std=c99 -Wall -Wextra -pedantic -o test_tutti test_tutti.c -lm \
	&& ./test_tutti \
	&& cvlc --play-and-exit output.wav