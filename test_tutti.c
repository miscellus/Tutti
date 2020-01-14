
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
	//(float *samples, int num_samples, float frequency, float duration, float at, float volume)

	(void)volume;

	float old_signal = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		float signal;
		signal  = 0.4*tut_wave_saw(frequency * (at + t*duration));
		signal += 0.3*tut_wave_triangle(frequency * (at + t*duration));
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
		old_signal = 0.95*old_signal + 0.05*signal;
		samples[i] = old_signal;
	}

	return 0;
}

static TUT_INSTRUMENT(instrument_drum) {
	//(float *samples, int num_samples, float frequency, float duration, double at, float volume)

	(void)volume;
	(void)duration;

	double frequency_end = tut_max(frequency*0.5, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;

	float inv_samples_per_second = 1.0/tut_state.sample_rate;

	float envelope_amplitude[] = {
	// time    amplitude
		0,        0,
		0.1,      1,
		0.4,      0.1,
		0.9,      0.05,
		1,        0,
	};

	float envelope_noise[] = {
		0,     0.7,
		0.01,  0.1,
		0.1,   0,
	};

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		
		float tone = 0;
		tone += tut_wave_sine(at * inv_samples_per_second);
		tone += 0.3*tut_wave_square(at * inv_samples_per_second);

		float noise = ((float)rand()/(float)RAND_MAX * 2 - 1);

		tone *= tut_envelope(t, envelope_amplitude, TUT_NUM_ELEMS(envelope_amplitude));
		noise *= tut_envelope(t, envelope_noise, TUT_NUM_ELEMS(envelope_noise));

		samples[i] = tone + noise;
		
		at += frequency;
		frequency += frequency_quantum;
	}

	return 0;
}

static TUT_INSTRUMENT(instrument_snare_drum) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float volume)

	(void)volume;
	(void)duration;

	double frequency_end = tut_max(frequency*0.5, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;

	float inv_samples_per_second = 1.0/tut_state.sample_rate;

	float envelope_amplitude[] = {
	// time    amplitude
		0,       0,
		0.01,    1,
		0.1,     0,
	};

	float envelope_noise[] = {
		0,     0.0,
		0.001, 1,
		0.1,   0.1,
		1,     0,
	};

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		
		float tone = 0;
		tone += tut_wave_sine(at * inv_samples_per_second);
		tone += 0.3*tut_wave_square(at * inv_samples_per_second);
		tone *= tut_envelope(t, envelope_amplitude, TUT_NUM_ELEMS(envelope_amplitude));

		float noise = ((float)rand()/(float)RAND_MAX * 2 - 1);
		noise *= tut_envelope(t, envelope_noise, TUT_NUM_ELEMS(envelope_noise));

		samples[i] = tone + noise;
		
		at += frequency;
		frequency += frequency_quantum;
	}

	return 0;
}

static TUT_INSTRUMENT(instrument_hihat) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float volume)

	(void)volume;
	(void)at;
	(void)frequency;
	(void)duration;

	float old_signal = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);

		float signal = ((float)rand()/(float)RAND_MAX)*2 - 1;

		float envelope = 1;


		if (t > 0.07) {
			envelope = 1-(t-0.07)/(1-0.07);
			envelope *= envelope;
			envelope *= 0.5;
		}

		signal *= envelope;

		old_signal = 0.95*old_signal + 0.05*signal;

		samples[i] = signal - old_signal;
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

static Tut_Timeline make_arpeggio_piano_timeline() {
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
			case 'a': play_triade(C5, f5, A5); break;
			case 'b': play_triade(c5, f5, A5); break;
			case 'c': play_triade(c5, f5, G5); break;
		}
	}

	tut_gen_samples(&tl);

	return tl;
}

static Tut_Timeline make_bass_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);
	tut_instrument(instrument_cello_ish);

	tut_play(A2, 8);
	tut_play(A3, 8);
	tut_advance(24);

	tut_play(c3, 8);
	tut_play(c4, 8);
	tut_advance(8);
	
	tut_play(f2, 16);
	tut_play(f3, 16);
	tut_advance(24);
	
	tut_play(f2, 8);
	tut_play(f3, 8);
	tut_advance(8);

	tut_gen_samples(&tl);
	return tl;
}


static Tut_Timeline make_drum_timeline() {
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
				tut_play(70, 4.48);
				break;
			case 's':
				tut_volume(0.5);
				tut_instrument(instrument_snare_drum);
				tut_play(200, 1.86);
				break;
			case 'h':
				tut_volume(0.3);
				tut_instrument(instrument_hihat);
				tut_play(700, 4.96);
				break;
		}
		// if ((drum_seq.index & 1) == 0) {
		// 	tut_volume((drum_seq.index & 1) ? 0.1 : 0.2);
		// 	tut_instrument(instrument_hihat);
		// 	tut_play(1000, 1.24);
		// }
		tut_advance(1);
	}

	tut_gen_samples(&tl);
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
				tut_play(f2, 16);
				tut_play(f3, 16);
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

	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
