#include "tutti.h"
#include <stdio.h>
#include <stdlib.h>

#define BEATS_PER_MINUTE    93
#define SECONDS_PER_BEAT    60.0/BEATS_PER_MINUTE
#define INTERVALS_PER_BEAT  8
#define BEATS_PER_BAR       4
#define INTERVALS_PER_BAR   INTERVALS_PER_BEAT*BEATS_PER_BAR
#define SPI                 SECONDS_PER_BEAT/INTERVALS_PER_BEAT

static Tut_Timeline make_arpeggio_piano_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);

	int interval = 0;

	for (int i = 0; i < 8; ++i, interval += 4) {
		tut_to(interval*SPI);

		tut_play_stay(C5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(f5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(A5, 2*SPI);
	}

	for (int i = 0; i < 3; ++i, interval += 4) {
		tut_to(interval*SPI);

		tut_play_stay(c5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(f5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(A5, 2*SPI);
	}

	for (int i = 0; i < 5; ++i, interval += 4) {
		tut_to(interval*SPI);

		tut_play_stay(c5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(f5, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(G5, 2*SPI);
	}

	tut_gen_samples(&tl);

	return tl;
}

static Tut_Timeline make_bass_piano_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);

	tut_play_stay(A2, 8*SPI);
	tut_play(A3, 8*SPI);

	tut_advance(2*8*SPI);

	tut_play_stay(c3, 8*SPI);
	tut_play(c4, 8*SPI);
	tut_play_stay(f2, 2*8*SPI);
	tut_play(f3, 2*8*SPI);

	tut_advance(8*SPI);

	tut_play_stay(f2, 8*SPI);
	tut_play(f3, 8*SPI);

	tut_gen_samples(&tl);
	return tl;
}

int main(void) {

	Tut_Timeline main_timeline = tut_make_timeline();
	Tut_Timeline arpeggio_piano_timeline = make_arpeggio_piano_timeline();
	Tut_Timeline bass_piano_timeline = make_bass_piano_timeline();

	tut_timeline(&main_timeline);
	tut_to(0);

	for (int i = 0; i < 4; ++i) {
		tut_velocity(0.9);
		tut_play_timeline_stay(&arpeggio_piano_timeline);
		tut_velocity(1);
		tut_play_timeline(&bass_piano_timeline);
	}

	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
