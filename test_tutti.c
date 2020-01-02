#include "tutti.h"
#include <stdio.h>
#include <stdlib.h>

#define CHAN_MELODY 0
#define CHAN_BASS 1

int main(void) {

	Tut_Song song = tut_make_song();

	tut_set_song(&song);


	int last_pick = 0;

	double f[] = {a3, e3, b3, F3, C3, G3, D3, A3, a4, e4, b4, F4, C4, G4, D4, A4};
	// double f[] = {e3, a3, A3, b3, c4, C4, d4, D4, e4, f4, F4, g4, G4, a4, A4, b4, c5, C5, d5, D5, e5, f5, F5, g5, G5, a5, A5, b5, c6, C6, d6, D6, e6, f6, F6, g6, G6, a6, A6, b6};

	int pick = tut_static_array_len(f)/2;

	for (int i = 0; i < 64; ++i) {
		while (pick == last_pick) {
			pick = (last_pick + tut_static_array_len(f) + ((rand()%6) - 3)) % tut_static_array_len(f);
		}

		tut_duration(0.1); tut_play(f[pick]);
		tut_duration(0.05); tut_rest();

		last_pick = pick;
	}

	tut_finalize_song();

	FILE *file = fopen("output.wav", "wb");
	tut_write_wave_file(file);
	fclose(file);

	return 0;
}
