#include "tutti.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	Tut_Timeline main_timeline = tut_make_timeline();
	tut_timeline(&main_timeline);
	// Tut_Timeline melody_pat_1 = tut_make_timeline();
	// Tut_Timeline melody_pat_2 = tut_make_timeline();
	// Tut_Timeline drum_beat_1 = tut_make_timeline();

	double beats_per_minute = 79;
	double seconds_per_beat = 60.0/beats_per_minute;
	double intervals_per_beat = 24;

	double seconds_per_interval = seconds_per_beat/intervals_per_beat;

	tut_time_scale(seconds_per_interval);

	// tut_amplitude(0.5f);
	// tut_play_sub_timeline(&drum_beat_1);
	// tut_pan(-0.5f);
	// tut_play_sub_timeline(&melody_pat_1);
	// tut_pan(0.5f);
	// tut_play_sub_timeline(&melody_pat_2);

	tut_to(3);
	tut_play(1000, 0.5);
	tut_to(0);
	
	int last_pick = 0;

	double f[] = {a3, e3, b3, F3, C3, G3, D3, A3, a4, e4, b4, F4, C4, G4, D4, A4};
	// double f[] = {e3, a3, A3, b3, c4, C4, d4, D4, e4, f4, F4, g4, G4, a4, A4, b4, c5, C5, d5, D5, e5, f5, F5, g5, G5, a5, A5, b5, c6, C6, d6, D6, e6, f6, F6, g6, G6, a6, A6, b6};

	int pick = tut_static_array_len(f)/2;

	for (int i = 0; i < 32; ++i) {
		while (pick == last_pick) {
			pick = (last_pick + tut_static_array_len(f) + ((rand()%8) - 4)) % tut_static_array_len(f);
		}
		last_pick = pick;

		tut_play(c4, 4 * seconds_per_interval);
		tut_advance(4 * seconds_per_interval);
		tut_play(f[(pick + 2) % tut_static_array_len(f) ], 8 * seconds_per_interval);
		tut_play(c4, 3 * seconds_per_interval);
		tut_advance(2 * seconds_per_interval);
		tut_play(f[pick], 3 * seconds_per_interval);
	}

	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
