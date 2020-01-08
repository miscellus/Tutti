#ifndef TUTTI
#define TUTTI

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef TAU
#define TAU 6.283185307179586
#endif

/* Step sizes */
#define s57 0.03716272234383503  //2**(-57/12)
#define s56 0.03937253280921478  //2**(-56/12)
#define s55 0.04171374544281358  //2**(-55/12)
#define s54 0.04419417382415922  //2**(-54/12)
#define s53 0.04682209615239629  //2**(-53/12)
#define s52 0.049606282874006244 //2**(-52/12)
#define s51 0.052556025953357156 //2**(-51/12)
#define s50 0.0556811698837712   //2**(-50/12)
#define s49 0.05899214454260585  //2**(-49/12)
#define s48 0.0625               //2**(-48/12)
#define s47 0.06621644339745596  //2**(-47/12)
#define s46 0.0701538780193358   //2**(-46/12)
#define s45 0.07432544468767006  //2**(-45/12)
#define s44 0.07874506561842957  //2**(-44/12)
#define s43 0.08342749088562713  //2**(-43/12)
#define s42 0.08838834764831845  //2**(-42/12)
#define s41 0.09364419230479261  //2**(-41/12)
#define s40 0.09921256574801246  //2**(-40/12)
#define s39 0.10511205190671431  //2**(-39/12)
#define s38 0.11136233976754242  //2**(-38/12)
#define s37 0.11798428908521168  //2**(-37/12)
#define s36 0.125                //2**(-36/12)
#define s35 0.1324328867949119   //2**(-35/12)
#define s34 0.1403077560386716   //2**(-34/12)
#define s33 0.14865088937534013  //2**(-33/12)
#define s32 0.15749013123685915  //2**(-32/12)
#define s31 0.16685498177125427  //2**(-31/12)
#define s30 0.1767766952966369   //2**(-30/12)
#define s29 0.18728838460958522  //2**(-29/12)
#define s28 0.19842513149602492  //2**(-28/12)
#define s27 0.21022410381342863  //2**(-27/12)
#define s26 0.22272467953508485  //2**(-26/12)
#define s25 0.23596857817042335  //2**(-25/12)
#define s24 0.25                 //2**(-24/12)
#define s23 0.2648657735898238   //2**(-23/12)
#define s22 0.28061551207734325  //2**(-22/12)
#define s21 0.29730177875068026  //2**(-21/12)
#define s20 0.3149802624737183   //2**(-20/12)
#define s19 0.3337099635425086   //2**(-19/12)
#define s18 0.3535533905932738   //2**(-18/12)
#define s17 0.3745767692191704   //2**(-17/12)
#define s16 0.3968502629920499   //2**(-16/12)
#define s15 0.42044820762685725  //2**(-15/12)
#define s14 0.44544935907016964  //2**(-14/12)
#define s13 0.47193715634084676  //2**(-13/12)
#define s12 0.5                  //2**(-12/12)
#define s11 0.5297315471796477   //2**(-11/12)
#define s10 0.5612310241546865   //2**(-10/12)
#define s9  0.5946035575013605   //2**(-9/12)
#define s8  0.6299605249474366   //2**(-8/12)
#define s7  0.6674199270850172   //2**(-7/12)
#define s6  0.7071067811865476   //2**(-6/12)
#define s5  0.7491535384383408   //2**(-5/12)
#define s4  0.7937005259840998   //2**(-4/12)
#define s3  0.8408964152537145   //2**(-3/12)
#define s2  0.8908987181403393   //2**(-2/12)
#define s1  0.9438743126816935   //2**(-1/12)
#define S1  1.0594630943592953   //2**(1/12)
#define S2  1.122462048309373    //2**(2/12)
#define S3  1.189207115002721    //2**(3/12)
#define S4  1.2599210498948732   //2**(4/12)
#define S5  1.3348398541700344   //2**(5/12)
#define S6  1.4142135623730951   //2**(6/12)
#define S7  1.4983070768766815   //2**(7/12)
#define S8  1.5874010519681994   //2**(8/12)
#define S9  1.681792830507429    //2**(9/12)
#define S10 1.7817974362806785   //2**(10/12)
#define S11 1.8877486253633868   //2**(11/12)
#define S12 2.0                  //2**(12/12)
#define S13 2.1189261887185906   //2**(13/12)
#define S14 2.244924096618746    //2**(14/12)
#define S15 2.378414230005442    //2**(15/12)
#define S16 2.5198420997897464   //2**(16/12)
#define S17 2.6696797083400687   //2**(17/12)
#define S18 2.8284271247461903   //2**(18/12)
#define S19 2.996614153753363    //2**(19/12)
#define S20 3.174802103936399    //2**(20/12)
#define S21 3.363585661014858    //2**(21/12)
#define S22 3.563594872561357    //2**(22/12)
#define S23 3.775497250726774    //2**(23/12)
#define S24 4.0                  //2**(24/12)
#define S25 4.237852377437181    //2**(25/12)
#define S26 4.489848193237491    //2**(26/12)
#define S27 4.756828460010884    //2**(27/12)
#define S28 5.039684199579493    //2**(28/12)
#define S29 5.339359416680137    //2**(29/12)
#define S30 5.656854249492381    //2**(30/12)
#define S31 5.993228307506727    //2**(31/12)
#define S32 6.3496042078727974   //2**(32/12)
#define S33 6.727171322029716    //2**(33/12)
#define S34 7.127189745122715    //2**(34/12)
#define S35 7.550994501453547    //2**(35/12)
#define S36 8.0                  //2**(36/12)
#define S37 8.475704754874362    //2**(37/12)
#define S38 8.979696386474982    //2**(38/12)
#define S39 9.513656920021768    //2**(39/12)
#define S40 10.079368399158986   //2**(40/12)
#define S41 10.678718833360273   //2**(41/12)
#define S42 11.313708498984761   //2**(42/12)
#define S43 11.986456615013454   //2**(43/12)
#define S44 12.699208415745595   //2**(44/12)
#define S45 13.454342644059432   //2**(45/12)
#define S46 14.25437949024543    //2**(46/12)
#define S47 15.101989002907095   //2**(47/12)
#define S48 16.0                 //2**(48/12)
#define S49 16.95140950974872    //2**(49/12)
#define S50 17.959392772949972   //2**(50/12)

/*
Note Frequency in hertz (Wavelength in centimeters)
*/

#define CONCERT_PITCH 440

#define c0 (s57 * CONCERT_PITCH)
#define C0 (s56 * CONCERT_PITCH)
#define d0 (s55 * CONCERT_PITCH)
#define D0 (s54 * CONCERT_PITCH)
#define e0 (s53 * CONCERT_PITCH)
#define f0 (s52 * CONCERT_PITCH)
#define F0 (s51 * CONCERT_PITCH)
#define g0 (s50 * CONCERT_PITCH)
#define G0 (s49 * CONCERT_PITCH)
#define a0 (s48 * CONCERT_PITCH)
#define A0 (s47 * CONCERT_PITCH)
#define b0 (s46 * CONCERT_PITCH)
#define c1 (s45 * CONCERT_PITCH)
#define C1 (s44 * CONCERT_PITCH)
#define d1 (s43 * CONCERT_PITCH)
#define D1 (s42 * CONCERT_PITCH)
#define e1 (s41 * CONCERT_PITCH)
#define f1 (s40 * CONCERT_PITCH)
#define F1 (s39 * CONCERT_PITCH)
#define g1 (s38 * CONCERT_PITCH)
#define G1 (s37 * CONCERT_PITCH)
#define a1 (s36 * CONCERT_PITCH)
#define A1 (s35 * CONCERT_PITCH)
#define b1 (s34 * CONCERT_PITCH)
#define c2 (s33 * CONCERT_PITCH)
#define C2 (s32 * CONCERT_PITCH)
#define d2 (s31 * CONCERT_PITCH)
#define D2 (s30 * CONCERT_PITCH)
#define e2 (s29 * CONCERT_PITCH)
#define f2 (s28 * CONCERT_PITCH)
#define F2 (s27 * CONCERT_PITCH)
#define g2 (s26 * CONCERT_PITCH)
#define G2 (s25 * CONCERT_PITCH)
#define a2 (s24 * CONCERT_PITCH)
#define A2 (s23 * CONCERT_PITCH)
#define b2 (s22 * CONCERT_PITCH)
#define c3 (s21 * CONCERT_PITCH)
#define C3 (s20 * CONCERT_PITCH)
#define d3 (s19 * CONCERT_PITCH)
#define D3 (s18 * CONCERT_PITCH)
#define e3 (s17 * CONCERT_PITCH)
#define f3 (s16 * CONCERT_PITCH)
#define F3 (s15 * CONCERT_PITCH)
#define g3 (s14 * CONCERT_PITCH)
#define G3 (s13 * CONCERT_PITCH)
#define a3 (s12 * CONCERT_PITCH)
#define A3 (s11 * CONCERT_PITCH)
#define b3 (s10 * CONCERT_PITCH)
#define c4 (s9 * CONCERT_PITCH)
#define C4 (s8 * CONCERT_PITCH)
#define d4 (s7 * CONCERT_PITCH)
#define D4 (s6 * CONCERT_PITCH)
#define e4 (s5 * CONCERT_PITCH)
#define f4 (s4 * CONCERT_PITCH)
#define F4 (s3 * CONCERT_PITCH)
#define g4 (s2 * CONCERT_PITCH)
#define G4 (s1 * CONCERT_PITCH)
#define a4 CONCERT_PITCH
#define A4 (S1 * CONCERT_PITCH)
#define b4 (S2 * CONCERT_PITCH)
#define c5 (S3 * CONCERT_PITCH)
#define C5 (S4 * CONCERT_PITCH)
#define d5 (S5 * CONCERT_PITCH)
#define D5 (S6 * CONCERT_PITCH)
#define e5 (S7 * CONCERT_PITCH)
#define f5 (S8 * CONCERT_PITCH)
#define F5 (S9 * CONCERT_PITCH)
#define g5 (S10 * CONCERT_PITCH)
#define G5 (S11 * CONCERT_PITCH)
#define a5 (S12 * CONCERT_PITCH)
#define A5 (S13 * CONCERT_PITCH)
#define b5 (S14 * CONCERT_PITCH)
#define c6 (S15 * CONCERT_PITCH)
#define C6 (S16 * CONCERT_PITCH)
#define d6 (S17 * CONCERT_PITCH)
#define D6 (S18 * CONCERT_PITCH)
#define e6 (S19 * CONCERT_PITCH)
#define f6 (S20 * CONCERT_PITCH)
#define F6 (S21 * CONCERT_PITCH)
#define g6 (S22 * CONCERT_PITCH)
#define G6 (S23 * CONCERT_PITCH)
#define a6 (S24 * CONCERT_PITCH)
#define A6 (S25 * CONCERT_PITCH)
#define b6 (S26 * CONCERT_PITCH)
#define c7 (S27 * CONCERT_PITCH)
#define C7 (S28 * CONCERT_PITCH)
#define d7 (S29 * CONCERT_PITCH)
#define D7 (S30 * CONCERT_PITCH)
#define e7 (S31 * CONCERT_PITCH)
#define f7 (S32 * CONCERT_PITCH)
#define F7 (S33 * CONCERT_PITCH)
#define g7 (S34 * CONCERT_PITCH)
#define G7 (S35 * CONCERT_PITCH)
#define a7 (S36 * CONCERT_PITCH)
#define A7 (S37 * CONCERT_PITCH)
#define b7 (S38 * CONCERT_PITCH)
#define c8 (S39 * CONCERT_PITCH)
#define C8 (S40 * CONCERT_PITCH)
#define d8 (S41 * CONCERT_PITCH)
#define D8 (S42 * CONCERT_PITCH)
#define e8 (S43 * CONCERT_PITCH)
#define f8 (S44 * CONCERT_PITCH)
#define F8 (S45 * CONCERT_PITCH)
#define g8 (S46 * CONCERT_PITCH)
#define G8 (S47 * CONCERT_PITCH)
#define a8 (S48 * CONCERT_PITCH)
#define A8 (S49 * CONCERT_PITCH)
#define b8 (S50 * CONCERT_PITCH)

#define tut_static_array_len(A) \
	(sizeof(A)/sizeof(*(A)))

#define tut_offset_of(s,memb) \
	((size_t)((char *)&((s *)0)->memb - (char *)0))


#define TUT_SINE_MEAN_MAG 0.637
#define TUT_TRIANGLE_MEAN_MAG 0.5
#define TUT_SQUARE_MEAN_MAG 1

double tut_wave_sine(double v) {
	v = sin(TAU * v);
	v *= TUT_TRIANGLE_MEAN_MAG/TUT_SINE_MEAN_MAG;
	return v;
}

double tut_wave_triangle(double v) {
	v -= (double)(int64_t)v;

	if (v < 0.25) {
		v = v / 0.25;
	}
	else if (v < 0.75) {
		v = 1 - 2*((v - 0.25) / 0.5);
	}
	else {          
		v = -1 + (v - 0.75) / 0.25;
	}

	return v;
}

double tut_wave_square(double v) {
	v -= (double)(int64_t)v;

	if (v < 0.5) v = 1;
	else v = -1;

	v *= TUT_TRIANGLE_MEAN_MAG/TUT_SQUARE_MEAN_MAG;

	return v;
}

double tut_wave_saw(double v) {
	v += 0.5;
	v -= (double)(int64_t)v;
	v *= 2;
	v -= 1;

	// TODO(jakob): What is the rectified mean magnitude of a saw wave? 

	return v;
}

// enum {TUT_TIMELINE_BUCKET_ops_CAPACITY = 8};

// typedef struct Tut_Timeline_Bucket {
//  double pivot; // NOTE(jakob): the timestamp in seconds
//  union {
//      struct Tut_Timeline_Bucket *left;
//      struct Tut_Timeline_Bucket *right;
//  } u;
// } Tut_Timeline_Bucket;

// typedef struct Tut_Timeline {
	
// } Tut_Timeline;


typedef enum Tut_Export_File_Type {
	TUT_FILE_WAV = 0,
} Tut_Export_File_Type;

typedef enum Tut_Opcode {
	// DISREGARD(jakob): Ops will be sorted secondarily on the opcode, to
	// ensure that the appropriate effects have been applied before
	// TUT_OP_PLAY.

	TUT_OP_NONE = 0,
	TUT_OP_VELOCITY,
	TUT_OP_SUB_TIMELINE,
	TUT_OP_PLAY,
	Tut_Opcode__COUNT
} Tut_Opcode;


typedef struct Tut_Op_Play {
	Tut_Opcode opcode;
	float frequency;
	float duration;
} Tut_Op_Play;

typedef struct Tut_Op_Velocity {
	Tut_Opcode opcode;
	float velocity;
} Tut_Op_Velocity;

// typedef struct Tut_Op_Pan {
// 	Tut_Opcode opcode;
// 	float pan;
// } Tut_Op_Pan;

struct Tut_Timeline;

typedef struct Tut_Op_Sub_Timeline {
	Tut_Opcode opcode;
	struct Tut_Timeline *timeline;
} Tut_Op_Sub_Timeline;

typedef union Tut_Op {
	Tut_Opcode opcode;
	Tut_Op_Play play;
	Tut_Op_Velocity velocity;
	Tut_Op_Sub_Timeline sub_timeline;
} Tut_Op;

typedef struct Tut_Time_Op {
	float at;
	Tut_Op op;
} Tut_Time_Op;

typedef struct Tut_Timeline {
	size_t ops_capacity;
	uint64_t end_op_index;
	Tut_Time_Op *ops;

	size_t sample_capacity;
	uint64_t end_sample_index;
	float *samples;
} Tut_Timeline;

typedef struct Tut_Song {
	int16_t *samples;
	size_t num_samples;
	size_t used_samples;
} Tut_Song;

typedef struct Tut_Global_State {
	Tut_Timeline *timeline;
	float amplitude;
	float pan;
	float time_scale;
	float at;
	uint32_t sample_rate;
} Tut_Global_State;

static Tut_Global_State tut_state = {
	.sample_rate = 44100,
	.time_scale = 1,
	.amplitude = 0.8f,
};

static inline float tut_at(void) {
	return tut_state.at;
}

static inline float tut_to(float at) {
	return (tut_state.at = at);
}

static inline float tut_advance(float duration) {
	return tut_to(tut_at() + duration);
}

static inline void tut_time_scale(float time_scale) {
	tut_state.time_scale = time_scale;
}

static inline void tut_timeline(Tut_Timeline *timeline) {
	tut_state.timeline = timeline;
}

static inline Tut_Timeline tut_make_timeline(void) {
	Tut_Timeline result = {0};
	return result;
}

static void tut_push_op(Tut_Op op) {

	Tut_Timeline *tl = tut_state.timeline;

	if (tl->end_op_index >= tl->ops_capacity) {
		size_t new_ops_capacity = (tl->ops_capacity != 0) ? 2*tl->ops_capacity : 8;
		fprintf(stderr, "next size: %d\n", (int)(new_ops_capacity * sizeof(tl->ops[0])));
		void *new = realloc(tl->ops, new_ops_capacity * sizeof(tl->ops[0]));
		assert(new != NULL);

		if (new != tl->ops) {
			fprintf(stderr, "realloc !\n");
		}

		tl->ops = new;
		tl->ops_capacity = new_ops_capacity;
	}

	tl->ops[tl->end_op_index++] = (Tut_Time_Op){tut_at(), op};
}

static inline void tut_play_stay(float frequency, float duration) {
	tut_push_op((Tut_Op){.play={TUT_OP_PLAY, frequency, duration}});
}

static inline float tut_play(float frequency, float duration) {
	tut_play_stay(frequency, duration);
	return tut_advance(duration);
}

static inline void tut_velocity(float velocity) {
	tut_push_op((Tut_Op){.velocity={TUT_OP_VELOCITY, velocity}});
}

static inline float tut_play_sub_timeline(Tut_Timeline *tl) {

	tut_push_op((Tut_Op){.sub_timeline={TUT_OP_SUB_TIMELINE, tl}});

	float duration = (float)tl->end_sample_index / (float)tut_state.sample_rate;

	return tut_advance(duration);
}

static inline void tut_add_samples(Tut_Timeline *tl, float at, float *samples, size_t num_samples, float factor) {

	size_t start_sample_index = (size_t)(at * tut_state.sample_rate);
	size_t end_sample_index = start_sample_index + num_samples;

	if (end_sample_index >= tl->sample_capacity) {

		size_t new_sample_capacity = (tl->sample_capacity != 0) ? 2*tl->sample_capacity : tut_state.sample_rate;

		while (new_sample_capacity < end_sample_index) {
			new_sample_capacity *= 2;
		}

		void *new = realloc(tl->samples, new_sample_capacity * sizeof(tl->samples[0]));
		assert(new != NULL);

		fprintf(stderr, "REALLOCED from %d to %d samples.\n", (int)tl->sample_capacity, (int)new_sample_capacity);

		if (new != tl->samples) {
			fprintf(stderr, "realloc !\n");
		}

		tl->samples = new;

		// Zero fill
		memset(
			tl->samples + tl->sample_capacity,
			0,
			(new_sample_capacity - tl->sample_capacity) * sizeof(*tl->samples)
		);

		tl->sample_capacity = new_sample_capacity;
	}

	for (size_t i = 0; i < num_samples; ++i) {
		tl->samples[start_sample_index + i] += factor * samples[i];
	}

	if (end_sample_index > tl->end_sample_index) {
		tl->end_sample_index = end_sample_index;
	}
}

void tut_normalize_samples(Tut_Timeline *tl) {
	float max_amplitude = 0;

	for (size_t i = 0; i < tl->end_sample_index; ++i) {
		float sample = tl->samples[i];
		if (sample < 0) {
			sample = -sample;
		}

		if (sample > max_amplitude) {
			max_amplitude = sample;
		}
	}

	for (size_t i = 0; i < tl->end_sample_index; ++i) {
		tl->samples[i] /= max_amplitude;
	}
}

static int _tut_op_time_compare (const void * _a, const void * _b) {
	const Tut_Time_Op *a = _a;
	const Tut_Time_Op *b = _b;

	if (a->at == b->at) {
		return 0; //a->op.opcode - b->op.opcode;
	} 
	else {
		return (a->at < b->at) ? -1 : 1;
	}
}

static void tut_gen_samples(Tut_Timeline *tl) {
	if (tl->samples != NULL) {
		return;
	}

	qsort(tl->ops, tl->end_op_index, sizeof(tl->ops[0]), _tut_op_time_compare);
	
	float velocity = 1;

	for (uint64_t op_index = 0; op_index < tl->end_op_index; ++op_index) {

		Tut_Time_Op time_op = tl->ops[op_index];

		float at = time_op.at;
		Tut_Op op = time_op.op;

		switch (op.opcode) {
		case TUT_OP_SUB_TIMELINE:
			tut_gen_samples(op.sub_timeline.timeline);
			assert(op.sub_timeline.timeline->samples);
			tut_add_samples(tl, at, op.sub_timeline.timeline->samples, op.sub_timeline.timeline->end_sample_index, velocity);
		break;
		case TUT_OP_VELOCITY:
			velocity = op.velocity.velocity;
		break;
		case TUT_OP_PLAY: {
			int samples_per_duration = (int)(op.play.duration * tut_state.sample_rate);

			float *tmp_samples = malloc(samples_per_duration * sizeof(*tmp_samples));
			assert(tmp_samples);

			for (int i = 0; i < samples_per_duration; ++i) {
				float t = ((float)i/(float)samples_per_duration);
				float signal = tut_wave_triangle(op.play.frequency * (at + t*(op.play.duration)));
				signal *= 0.8;
				if (t < 0.01) {
					signal *= t/0.01;
				}
				else if (t > 0.3) {
					signal *= (1-(t-0.3)/(1-0.3));
				}
				tmp_samples[i] = signal;
			}

			tut_add_samples(tl, at, tmp_samples, (size_t)samples_per_duration, velocity);
			free(tmp_samples);
		
		} break;
		default:
			assert(!"Nah");
			return;
		}
	}

	tut_normalize_samples(tl);
}

static void tut_save_timeline_as_wave_file(Tut_Timeline *tl, FILE *file_handle) {
	#define four_chars(s) (uint32_t)((s[3]<<24) | (s[2]<<16) | (s[1]<<8) | s[0])


	typedef struct Wav_Header {
		// RIFF Header
		uint32_t riff_header; // Contains "RIFF"
		uint32_t wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
		uint32_t wave_header; // Contains "WAVE"
		
		// Format Header
		uint32_t fmt_header; // Contains "fmt " (includes trailing space)
		uint32_t fmt_chunk_size; // Should be 16 for PCM
		uint16_t audio_format; // Should be 1 for PCM. 3 for IEEE Float
		uint16_t num_channels;
		uint32_t sample_rate;
		uint32_t byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
		uint16_t sample_alignment; // num_channels * Bytes Per Sample
		uint16_t bit_depth; // Number of bits per sample
		
		// Data
		uint32_t data_header; // Contains "data"
		uint32_t data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
		// uint8_t bytes[]; // Remainder of wave file is bytes
	} Wav_Header;

	size_t num_samples = tl->end_sample_index;
	uint32_t sample_rate = tut_state.sample_rate;
	int16_t *samples = malloc(num_samples * sizeof(*samples));
	size_t sample_size = sizeof(*samples);

	for (int i = 0; i < (int)num_samples; ++i) {
		samples[i] = (int16_t)(tl->samples[i] * 0x8000);
	}

	size_t total_file_size = sizeof(Wav_Header) + num_samples*sample_size;
	
	Wav_Header wh;
	wh.riff_header = four_chars("RIFF");
	wh.wav_size = total_file_size - 8;
	wh.wave_header = four_chars("WAVE");

	wh.fmt_header = four_chars("fmt ");
	wh.fmt_chunk_size = 16;
	wh.audio_format = 1; // 1 for 16 bit signed int  ||  3 for IEEE 754 float
	wh.num_channels = 1;
	wh.sample_rate = sample_rate;
	wh.byte_rate = wh.sample_rate * wh.num_channels * sample_size;
	wh.sample_alignment = wh.num_channels * sample_size;
	wh.bit_depth = 8 * sample_size;
	wh.data_header = four_chars("data");
	wh.data_bytes = num_samples * sample_size;

	fwrite(&wh, sizeof(wh), 1, file_handle);
	fwrite(samples, sample_size, num_samples, file_handle);

	#undef four_chars
}


#endif