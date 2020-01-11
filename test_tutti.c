#include "tutti.h"
#include <stdio.h>
#include <stdlib.h>

#define BEATS_PER_MINUTE    93
#define SECONDS_PER_BEAT    60.0/BEATS_PER_MINUTE
#define INTERVALS_PER_BEAT  8
#define BEATS_PER_BAR       4
#define INTERVALS_PER_BAR   INTERVALS_PER_BEAT*BEATS_PER_BAR
#define SPI                 SECONDS_PER_BEAT/INTERVALS_PER_BEAT

static TUT_INSTRUMENT(instrument_cello_ish) {
    //(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		float signal;
		signal  = tut_wave_square(frequency * (at + t*duration));
		signal += 0.3*tut_wave_triangle(1.01*frequency * (at + t*duration));
		signal += 0.1*tut_wave_triangle(4*frequency * (at + t*duration));
		const float attack = 0.2;
		const float release = 0.8;
		signal *= 0.8;
		if (t < attack) {
			signal *= t/attack;
		}
		else if (t > release) {
			signal *= (1-(t-release)/(1-release));
		}
		samples[i] = signal;
	}
}

static TUT_INSTRUMENT(instrument_drum) {
    //(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		float frequency_bend = frequency;
		float time = t*duration;
		float signal  = tut_wave_square(frequency_bend * time);

		const float attack = 0.001;
		const float release = attack+0.2;
		float envelope = 1;

		if (t < attack) {
			envelope = t/attack;
		}
		else if (t > release) {
			envelope = (1-(t-release)/(1-release));
		}

		signal *= envelope;

		samples[i] = signal;
	}
}

static inline void play_triade(float frequency1, float frequency2, float frequency3) {
		tut_play_stay(frequency1, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(frequency2, 2*SPI);
		tut_advance(0.02);
		tut_play_stay(frequency3, 2*SPI);
}

static Tut_Timeline make_arpeggio_piano_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);
	tut_instrument(NULL);

	int interval = 0;

	for (int i = 0; i < 8; ++i, interval += 4) {
		tut_to(interval*SPI);
		play_triade(C5, f5, A5);
	}

	for (int i = 0; i < 3; ++i, interval += 4) {
		tut_to(interval*SPI);
		play_triade(c5, f5, A5);
	}

	for (int i = 0; i < 5; ++i, interval += 4) {
		tut_to(interval*SPI);
		play_triade(c5, f5, G5);
	}

	tut_gen_samples(&tl);

	return tl;
}

static Tut_Timeline make_bass_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);
	tut_instrument(instrument_cello_ish);

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

#define TUT_FOR_STRING(S, I) for (int i=0, c; (c=(S)[i]) != '\0'; ++i, tut_advance(I))

static Tut_Timeline make_drum_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);
	tut_instrument(instrument_drum);

	for (int j = 0; j < 4; ++j)
	{
		TUT_FOR_STRING("#..#..#.",2*SPI) {
			if (c == '#') {
				tut_play_stay(50, SPI);
			}
		}
	}
	
	tut_gen_samples(&tl);
	return tl;
}

int main(void) {

	Tut_Timeline main_timeline = tut_make_timeline();
	Tut_Timeline arpeggio_piano_timeline = make_arpeggio_piano_timeline();
	Tut_Timeline bass_piano_timeline = make_bass_timeline();
	Tut_Timeline drum_timeline = make_drum_timeline();

	tut_timeline(&main_timeline);
	tut_to(0);

	for (int i = 0; i < 4; ++i) {
		tut_velocity(1);
		tut_play_timeline_stay(&drum_timeline);
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
