gcc -g -O0 -std=c99 -no-pie -Wall -Wextra -pedantic -o example_song.out example_song.c -lm \
	&& ./example_song.out \
	&& cvlc --play-and-exit Still_D.R.E.wav || \
	gdb example_song.out