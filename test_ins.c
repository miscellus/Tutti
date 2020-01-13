
#include <stdio.h>
#include <stdlib.h>

#define TUT_INCLUDE_COMMON_NOTES
#include "tutti.h"

static TUT_INSTRUMENT(instrument_test) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float velocity)

	(void)velocity;

	double frequency_end = tut_max(frequency-20, 0);

	double frequency_quantum = (frequency_end - frequency)/num_samples;

	double f = frequency;

	float amplitude = 0.8;

	float inv_samples_per_second = 1.0/tut_state.sample_rate;

	float envelope[] = {
	// time    amplitude
		0,         0,
		0.001,     1,
		0.4,      0.1,
		0.9,      0.05,
		1,         0,
	};

	double pos = 0;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);

		amplitude = tut_envelope(t, envelope, sizeof(envelope)/sizeof(*envelope));
		
		samples[i] = amplitude * tut_wave_square(pos * inv_samples_per_second);
		
		pos += f;
		f += frequency_quantum;
	}

	return -0.01*duration;
}

int main(void) {

	Tut_Timeline main_timeline = tut_make_timeline();
	tut_timeline(&main_timeline);
	tut_to(0);
	tut_instrument(instrument_test);
	tut_to(0.1);
	tut_play_advance(60, 0.2);
	tut_advance(0.2);
	tut_play(0,0);
	tut_gen_samples(&main_timeline);

	FILE *file = fopen("output.wav", "wb");
	tut_save_timeline_as_wave_file(&main_timeline, file);
	fclose(file);

	return 0;
}
