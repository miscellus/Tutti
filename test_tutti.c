#include "tutti.h"
#include <stdio.h>
#include <stdlib.h>

#define BEATS_PER_MINUTE    93
#define SECONDS_PER_BEAT    60.0/BEATS_PER_MINUTE
#define INTERVALS_PER_BEAT  8
#define BEATS_PER_BAR       4
#define INTERVALS_PER_BAR   INTERVALS_PER_BEAT*BEATS_PER_BAR
#define SPI                 SECONDS_PER_BEAT/INTERVALS_PER_BEAT

static Tut_Timeline make_piano_beat_1() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);

	int interval = 0;

	for (int j = 0; j < 4; ++j) {

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
	}

	tut_gen_samples(&tl);

	return tl;
}

static Tut_Timeline make_piano_beat_2() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);

	tut_play_stay(A2, 16*SPI);
	tut_play_stay(A3, 16*SPI);

	tut_gen_samples(&tl);

	return tl;
}

int main(void) {

	Tut_Timeline main_timeline = tut_make_timeline();
	Tut_Timeline piano_beat_1 = make_piano_beat_1();
	Tut_Timeline piano_beat_2 = make_piano_beat_2();
	tut_timeline(&main_timeline);

	tut_to(0);
	tut_play_sub_timeline(&piano_beat_1);
	tut_to(0);
	tut_play_sub_timeline(&piano_beat_2);

	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
