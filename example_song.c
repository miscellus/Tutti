
#include <stdio.h>
#include <stdlib.h>

#define TUT_INCLUDE_COMMON_NOTES
#include "tutti.h"

#define BEATS_PER_MINUTE      93
#define SECONDS_PER_BEAT      60.0/BEATS_PER_MINUTE
#define INTERVALS_PER_BEAT    8
#define BEATS_PER_BAR         4
#define INTERVALS_PER_BAR     INTERVALS_PER_BEAT*BEATS_PER_BAR
#define SECONDS_PER_INTERVAL  SECONDS_PER_BEAT/INTERVALS_PER_BEAT

static TUT_INSTRUMENT(instrument_cello_ish) {
	(void)volume;

	float old_signal = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		float signal;
		signal  = 0.4*tut_wave_saw(frequency * (at + t*duration));
		signal += 0.3*tut_wave_triangle((0.5*frequency + 0.5) * (at + t*duration));
		signal += 0.1*tut_wave_triangle((4*frequency + 0.7) * (at + t*duration));
		const float attack = 0.4;
		const float release = 0.8;

		if (t < attack) {
			signal *= t/attack;
		}
		else if (t > release) {
			signal *= 1 - (t-release)/(1-release);
		}
		
		old_signal = 0.95*old_signal + 0.05*signal;
		samples[i] = old_signal;
	}

	return 0;
}

static double generic_drum(
	float *samples,
	int num_samples,
	double frequency,
	double frequency_end,
	double at,
	float *tone_envelope,
	int tone_envelope_points,
	float *noise_envelope,
	int noise_envelope_points
) {

	frequency_end = tut_max(frequency_end, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;
	double inv_samples_per_second = 1.0/tut_state.sample_rate;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		
		float tone = 0;
		tone += tut_wave_sine(at * inv_samples_per_second);
		tone += 0.3*tut_wave_square(at * inv_samples_per_second);

		float noise = ((float)rand()/(float)RAND_MAX * 2 - 1);

		tone *= tut_envelope(t, tone_envelope, tone_envelope_points);
		noise *= tut_envelope(t, noise_envelope, noise_envelope_points);

		samples[i] = tone + noise;
		
		at += frequency;
		frequency += frequency_quantum;
	}

	return 0;
}

static inline TUT_INSTRUMENT(instrument_drum) {
	(void)volume;
	(void)duration;

	static float tone_envelope[] = {
	// time    amplitude
		0,        0,
		0.1,      1,
		0.4,      0.1,
		0.9,      0.05,
		1,        0,
	};

	static float noise_envelope[] = {
		0,     0.7,
		0.01,  0.1,
		0.1,   0,
	};

	return generic_drum(
		samples,
		num_samples,
		frequency,
		frequency*0.5,
		at,
		tone_envelope,
		TUT_NUM_ELEMS(tone_envelope),
		noise_envelope,
		TUT_NUM_ELEMS(noise_envelope));
}

static inline TUT_INSTRUMENT(instrument_snare_drum) {
	(void)volume;
	(void)duration;

	static float tone_envelope[] = {
	// time    amplitude
		0,       0,
		0.01,    1,
		0.1,     0,
	};

	static float noise_envelope[] = {
		0,     0.0,
		0.001, 1,
		0.1,   0.1,
		1,     0,
	};

	return generic_drum(
		samples,
		num_samples,
		frequency,
		frequency*0.5,
		at,
		tone_envelope,
		TUT_NUM_ELEMS(tone_envelope),
		noise_envelope,
		TUT_NUM_ELEMS(noise_envelope));
}

static TUT_INSTRUMENT(instrument_hihat) {
	(void)volume;
	(void)at;
	(void)frequency;
	(void)duration;

	float old_signal = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);

		float signal = ((float)rand()/(float)RAND_MAX)*2 - 1;
		old_signal = 0.99*old_signal + 0.01*signal;

		float envelope = 1;

		if (t > 0.07) {
			envelope = 1 - (t-0.07)/(1-0.07);
			envelope *= envelope;
			// envelope *= 0.5;
		}


		samples[i] = (signal - old_signal) * envelope;
	}

	return 0;
}

static inline void play_triade(float frequency1, float frequency2, float frequency3) {
		tut_play(frequency1, 2);
		tut_advance(0.25);
		tut_play(frequency2, 2);
		tut_advance(0.25);
		tut_play(frequency3, 2);
}

static Tut_Timeline make_arpeggio_piano_timeline(void) {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);
	tut_instrument(NULL);

	TUT_SEQUENCE(seq, char,
		"aaaaaaaa"
		"bbb"
		"ccccc"
	) {
		tut_to(4*seq.index);
		
		switch (seq.symbol) {
			case 'a': play_triade(TUT_C5, TUT_f5, TUT_A5); break;
			case 'b': play_triade(TUT_c5, TUT_f5, TUT_A5); break;
			case 'c': play_triade(TUT_c5, TUT_f5, TUT_G5); break;
		}
	}

	return tl;
}

static Tut_Timeline make_bass_timeline(void) {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);

	tut_to(0);
	tut_instrument(instrument_cello_ish);
	tut_play(TUT_A2, 8);
	tut_play(TUT_A3, 8);

	tut_to(24);
	tut_play(TUT_c3, 8);
	tut_play(TUT_c4, 8);
	
	tut_to(32);
	tut_play(TUT_f2, 16);
	tut_play(TUT_f3, 16);
	
	tut_to(56);
	tut_play(TUT_f2, 8);
	tut_play(TUT_f3, 8);

	return tl;
}


static Tut_Timeline make_drum_timeline(void) {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);

	TUT_SEQUENCE(drum_seq, char,
		"K---h---s--K----K---h---s-------"
		"K---h---s--K----K---h---s-------"
	) {
		tut_volume(1);
		switch(drum_seq.symbol) {
			case 'K':
				tut_volume(1);
				tut_instrument(instrument_drum);
				tut_play(70, 2);
				break;
			case 's':
				tut_volume(0.5);
				tut_instrument(instrument_snare_drum);
				tut_play(200, 2);
				break;
			case 'h':
				tut_volume(0.2);
				tut_instrument(instrument_hihat);
				tut_play(700, 6);
				break;
		}
		if ((drum_seq.index & 1) == 0) {
			tut_volume((drum_seq.index & 1) ? 0.09 : 0.08);
			tut_instrument(instrument_hihat);
			tut_play(1000, 0.5);
		}
		tut_advance(1);
	}

	return tl;
}

int main(void) {

	tut_time_scale(SECONDS_PER_INTERVAL);

	Tut_Timeline main_timeline = tut_make_timeline();
	Tut_Timeline arpeggio_piano_timeline = make_arpeggio_piano_timeline();
	Tut_Timeline bass_piano_timeline = make_bass_timeline();
	Tut_Timeline drum_timeline = make_drum_timeline();


	tut_timeline(&main_timeline);
	tut_to(0);
	tut_instrument(instrument_cello_ish);

	TUT_SEQUENCE(main_seq, int, (int[]){
		1,
		2, 2,
		3, 3, 3, 3,
		0,
	}) {
		switch(main_seq.symbol) {
			
			case 1: {
				tut_volume(0.5);
				tut_play(TUT_f2, 16);
				tut_play(TUT_f3, 16);
				tut_advance(16);
				continue;
			}
			break;

			case 2: {
				tut_volume(0.5);
				tut_play_timeline(&arpeggio_piano_timeline);
				tut_play_timeline(&bass_piano_timeline);
			}
			break;

			case 3: {
				tut_volume(0.5);
				tut_play_timeline(&arpeggio_piano_timeline);
				tut_play_timeline(&bass_piano_timeline);
				tut_volume(1);
				tut_play_timeline(&drum_timeline);
			}
			break;
		}

		tut_advance(2*INTERVALS_PER_BAR);
	}

	FILE *file = fopen("Still_D.R.E.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}