
#include <stdio.h>
#include <stdlib.h>

#define TUT_INCLUDE_COMMON_NOTES
#include "tutti.h"

#define BEATS_PER_MINUTE    93
#define SECONDS_PER_BEAT    60.0/BEATS_PER_MINUTE
#define INTERVALS_PER_BEAT  8
#define BEATS_PER_BAR       4
#define INTERVALS_PER_BAR   INTERVALS_PER_BEAT*BEATS_PER_BAR
#define SPI                 SECONDS_PER_BEAT/INTERVALS_PER_BEAT

static TUT_INSTRUMENT(instrument_cello_ish) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

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
	//(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

	double frequency_end = tut_max(frequency*0.5, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;

	double f = frequency;

	float amplitude = 0.8;

	float inv_samples_per_second = 1.0/tut_state.sample_rate;

	float envelope[] = {
	// time    amplitude
		0,         0,
		0.1,    1,
		0.4,      0.1,
		0.9,      0.05,
		1,         0,
	};

	float env_noise[] = {
		0, 0.7,
		0.01, 0.1,
		0.1, 0,
	};

	double pos = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);

		amplitude = tut_envelope(t, envelope, sizeof(envelope)/sizeof(*envelope));
		
		float timbre = tut_wave_sine(pos * inv_samples_per_second) + 0.3*tut_wave_square(pos * inv_samples_per_second);
		float noise = ((float)rand()/(float)RAND_MAX * 2 - 1) * tut_envelope(t, env_noise, sizeof(env_noise)/sizeof(*env_noise));



		samples[i] = amplitude * timbre + noise;
		
		pos += f;
		f += frequency_quantum;
	}

	return 0;
}

static TUT_INSTRUMENT(instrument_snare_drum) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

	double frequency_end = tut_max(frequency*0.5, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;

	double f = frequency;

	float amplitude = 0.8;

	float inv_samples_per_second = 1.0/tut_state.sample_rate;

	float envelope[] = {
	// time    amplitude
		0,         0,
		0.01,    1,
		0.1,      0,
	};

	float env_noise[] = {
		0, 0.0,
		0.001, 1,
		0.1, 0.1,
		1, 0,
	};

	double pos = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);

		amplitude = tut_envelope(t, envelope, sizeof(envelope)/sizeof(*envelope));
		
		float timbre = tut_wave_sine(pos * inv_samples_per_second) + 0.3*tut_wave_square(pos * inv_samples_per_second);
		float noise = ((float)rand()/(float)RAND_MAX * 2 - 1) * tut_envelope(t, env_noise, sizeof(env_noise)/sizeof(*env_noise));



		samples[i] = amplitude * timbre + noise;
		
		pos += f;
		f += frequency_quantum;
	}

	return 0;
}

static TUT_INSTRUMENT(instrument_hihat) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;
	(void)at;

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
		tut_play(frequency1, 2*SPI);
		tut_advance(0.25*SPI);
		tut_play(frequency2, 2*SPI);
		tut_advance(0.25*SPI);
		tut_play(frequency3, 2*SPI);
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

	tut_play(A2, 8*SPI);
	tut_play_advance(A3, 8*SPI);

	tut_advance(2*8*SPI);

	tut_play(c3, 8*SPI);
	tut_play_advance(c4, 8*SPI);

	tut_play(f2, 2*8*SPI);
	tut_play_advance(f3, 2*8*SPI);

	tut_advance(8*SPI);

	tut_play(f2, 8*SPI);
	tut_play_advance(f3, 8*SPI);

	tut_gen_samples(&tl);
	return tl;
}


static Tut_Timeline make_drum_timeline() {
	Tut_Timeline tl = tut_make_timeline();
	tut_timeline(&tl);
	tut_to(0);

	TUT_SEQUENCE(
	"K---h---s--K----K---h---s-------"
	"K---h---s--K----K---h---s-------"
	,SPI) {
		tut_velocity(1);
		switch(_c) {
			case 'K':
				tut_instrument(instrument_drum);
				break;
			case 's':
				tut_instrument(instrument_snare_drum);
				break;
			case 'h':
				tut_instrument(instrument_hihat);
				break;
		}
		switch(_c) {
			case 'K': tut_play(70, 0.2); break;
			case 's': tut_play(200, 0.15); break;
			case 'h': tut_play(700, 0.4); break;
		}
		// if ((_i & 1) == 0) {
		// 	tut_velocity((_i&1) ? 0.1 : 0.2);
		// 	tut_instrument(instrument_hihat);
		// 	tut_play(1000, 0.1);
		// }
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
	tut_instrument(instrument_cello_ish);

	tut_velocity(0.5);
	tut_play(f2, 16*SPI);
	tut_play_advance(f3, 16*SPI);

	tut_play_timeline(&arpeggio_piano_timeline);
	tut_play_timeline(&bass_piano_timeline);
	tut_advance(64*SPI);

	for (int i = 0; i < 3; ++i) {
		tut_velocity(1);
		tut_play_timeline(&drum_timeline);
		tut_velocity(0.5);
		tut_play_timeline(&arpeggio_piano_timeline);
		tut_play_timeline(&bass_piano_timeline);
		tut_advance(64*SPI);
	}

	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
