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

#ifndef TUT_PI
#define TUT_PI 3.141592653589793
#endif

#ifndef TUT_TAU
#define TUT_TAU 6.283185307179586
#endif

#define tut_max(a, b) ((a)>(b)?(a):(b))
#define tut_min(a, b) ((a)<(b)?(a):(b))
#define tut_clamp(a, min, max) tut_max(tut_min(a, (max)), (min))
#define tut_lerp(a, b, t) ((1-(t))*(a)+(t)*(b))

#ifdef TUT_INCLUDE_COMMON_NOTES
/* Step sizes */
#define TUT_s57 0.03716272234383503  //2**(-57/12)
#define TUT_s56 0.03937253280921478  //2**(-56/12)
#define TUT_s55 0.04171374544281358  //2**(-55/12)
#define TUT_s54 0.04419417382415922  //2**(-54/12)
#define TUT_s53 0.04682209615239629  //2**(-53/12)
#define TUT_s52 0.049606282874006244 //2**(-52/12)
#define TUT_s51 0.052556025953357156 //2**(-51/12)
#define TUT_s50 0.0556811698837712   //2**(-50/12)
#define TUT_s49 0.05899214454260585  //2**(-49/12)
#define TUT_s48 0.0625               //2**(-48/12)
#define TUT_s47 0.06621644339745596  //2**(-47/12)
#define TUT_s46 0.0701538780193358   //2**(-46/12)
#define TUT_s45 0.07432544468767006  //2**(-45/12)
#define TUT_s44 0.07874506561842957  //2**(-44/12)
#define TUT_s43 0.08342749088562713  //2**(-43/12)
#define TUT_s42 0.08838834764831845  //2**(-42/12)
#define TUT_s41 0.09364419230479261  //2**(-41/12)
#define TUT_s40 0.09921256574801246  //2**(-40/12)
#define TUT_s39 0.10511205190671431  //2**(-39/12)
#define TUT_s38 0.11136233976754242  //2**(-38/12)
#define TUT_s37 0.11798428908521168  //2**(-37/12)
#define TUT_s36 0.125                //2**(-36/12)
#define TUT_s35 0.1324328867949119   //2**(-35/12)
#define TUT_s34 0.1403077560386716   //2**(-34/12)
#define TUT_s33 0.14865088937534013  //2**(-33/12)
#define TUT_s32 0.15749013123685915  //2**(-32/12)
#define TUT_s31 0.16685498177125427  //2**(-31/12)
#define TUT_s30 0.1767766952966369   //2**(-30/12)
#define TUT_s29 0.18728838460958522  //2**(-29/12)
#define TUT_s28 0.19842513149602492  //2**(-28/12)
#define TUT_s27 0.21022410381342863  //2**(-27/12)
#define TUT_s26 0.22272467953508485  //2**(-26/12)
#define TUT_s25 0.23596857817042335  //2**(-25/12)
#define TUT_s24 0.25                 //2**(-24/12)
#define TUT_s23 0.2648657735898238   //2**(-23/12)
#define TUT_s22 0.28061551207734325  //2**(-22/12)
#define TUT_s21 0.29730177875068026  //2**(-21/12)
#define TUT_s20 0.3149802624737183   //2**(-20/12)
#define TUT_s19 0.3337099635425086   //2**(-19/12)
#define TUT_s18 0.3535533905932738   //2**(-18/12)
#define TUT_s17 0.3745767692191704   //2**(-17/12)
#define TUT_s16 0.3968502629920499   //2**(-16/12)
#define TUT_s15 0.42044820762685725  //2**(-15/12)
#define TUT_s14 0.44544935907016964  //2**(-14/12)
#define TUT_s13 0.47193715634084676  //2**(-13/12)
#define TUT_s12 0.5                  //2**(-12/12)
#define TUT_s11 0.5297315471796477   //2**(-11/12)
#define TUT_s10 0.5612310241546865   //2**(-10/12)
#define TUT_s9  0.5946035575013605   //2**(-9/12)
#define TUT_s8  0.6299605249474366   //2**(-8/12)
#define TUT_s7  0.6674199270850172   //2**(-7/12)
#define TUT_s6  0.7071067811865476   //2**(-6/12)
#define TUT_s5  0.7491535384383408   //2**(-5/12)
#define TUT_s4  0.7937005259840998   //2**(-4/12)
#define TUT_s3  0.8408964152537145   //2**(-3/12)
#define TUT_s2  0.8908987181403393   //2**(-2/12)
#define TUT_s1  0.9438743126816935   //2**(-1/12)
#define TUT_s0  1                    //2**(-0/12)
#define TUT_S0  1                    //2**(0/12)
#define TUT_S1  1.0594630943592953   //2**(1/12)
#define TUT_S2  1.122462048309373    //2**(2/12)
#define TUT_S3  1.189207115002721    //2**(3/12)
#define TUT_S4  1.2599210498948732   //2**(4/12)
#define TUT_S5  1.3348398541700344   //2**(5/12)
#define TUT_S6  1.4142135623730951   //2**(6/12)
#define TUT_S7  1.4983070768766815   //2**(7/12)
#define TUT_S8  1.5874010519681994   //2**(8/12)
#define TUT_S9  1.681792830507429    //2**(9/12)
#define TUT_S10 1.7817974362806785   //2**(10/12)
#define TUT_S11 1.8877486253633868   //2**(11/12)
#define TUT_S12 2.0                  //2**(12/12)
#define TUT_S13 2.1189261887185906   //2**(13/12)
#define TUT_S14 2.244924096618746    //2**(14/12)
#define TUT_S15 2.378414230005442    //2**(15/12)
#define TUT_S16 2.5198420997897464   //2**(16/12)
#define TUT_S17 2.6696797083400687   //2**(17/12)
#define TUT_S18 2.8284271247461903   //2**(18/12)
#define TUT_S19 2.996614153753363    //2**(19/12)
#define TUT_S20 3.174802103936399    //2**(20/12)
#define TUT_S21 3.363585661014858    //2**(21/12)
#define TUT_S22 3.563594872561357    //2**(22/12)
#define TUT_S23 3.775497250726774    //2**(23/12)
#define TUT_S24 4.0                  //2**(24/12)
#define TUT_S25 4.237852377437181    //2**(25/12)
#define TUT_S26 4.489848193237491    //2**(26/12)
#define TUT_S27 4.756828460010884    //2**(27/12)
#define TUT_S28 5.039684199579493    //2**(28/12)
#define TUT_S29 5.339359416680137    //2**(29/12)
#define TUT_S30 5.656854249492381    //2**(30/12)
#define TUT_S31 5.993228307506727    //2**(31/12)
#define TUT_S32 6.3496042078727974   //2**(32/12)
#define TUT_S33 6.727171322029716    //2**(33/12)
#define TUT_S34 7.127189745122715    //2**(34/12)
#define TUT_S35 7.550994501453547    //2**(35/12)
#define TUT_S36 8.0                  //2**(36/12)
#define TUT_S37 8.475704754874362    //2**(37/12)
#define TUT_S38 8.979696386474982    //2**(38/12)
#define TUT_S39 9.513656920021768    //2**(39/12)
#define TUT_S40 10.079368399158986   //2**(40/12)
#define TUT_S41 10.678718833360273   //2**(41/12)
#define TUT_S42 11.313708498984761   //2**(42/12)
#define TUT_S43 11.986456615013454   //2**(43/12)
#define TUT_S44 12.699208415745595   //2**(44/12)
#define TUT_S45 13.454342644059432   //2**(45/12)
#define TUT_S46 14.25437949024543    //2**(46/12)
#define TUT_S47 15.101989002907095   //2**(47/12)
#define TUT_S48 16.0                 //2**(48/12)
#define TUT_S49 16.95140950974872    //2**(49/12)
#define TUT_S50 17.959392772949972   //2**(50/12)

/*
Note Frequency in hertz (Wavelength in centimeters)
*/

#ifndef TUT_CONCERT_PITCH
#define TUT_CONCERT_PITCH 440
#endif

#define TUT_c0 (TUT_s57 * TUT_CONCERT_PITCH)
#define TUT_C0 (TUT_s56 * TUT_CONCERT_PITCH)
#define TUT_d0 (TUT_s55 * TUT_CONCERT_PITCH)
#define TUT_D0 (TUT_s54 * TUT_CONCERT_PITCH)
#define TUT_e0 (TUT_s53 * TUT_CONCERT_PITCH)
#define TUT_f0 (TUT_s52 * TUT_CONCERT_PITCH)
#define TUT_F0 (TUT_s51 * TUT_CONCERT_PITCH)
#define TUT_g0 (TUT_s50 * TUT_CONCERT_PITCH)
#define TUT_G0 (TUT_s49 * TUT_CONCERT_PITCH)
#define TUT_a0 (TUT_s48 * TUT_CONCERT_PITCH)
#define TUT_A0 (TUT_s47 * TUT_CONCERT_PITCH)
#define TUT_b0 (TUT_s46 * TUT_CONCERT_PITCH)
#define TUT_c1 (TUT_s45 * TUT_CONCERT_PITCH)
#define TUT_C1 (TUT_s44 * TUT_CONCERT_PITCH)
#define TUT_d1 (TUT_s43 * TUT_CONCERT_PITCH)
#define TUT_D1 (TUT_s42 * TUT_CONCERT_PITCH)
#define TUT_e1 (TUT_s41 * TUT_CONCERT_PITCH)
#define TUT_f1 (TUT_s40 * TUT_CONCERT_PITCH)
#define TUT_F1 (TUT_s39 * TUT_CONCERT_PITCH)
#define TUT_g1 (TUT_s38 * TUT_CONCERT_PITCH)
#define TUT_G1 (TUT_s37 * TUT_CONCERT_PITCH)
#define TUT_a1 (TUT_s36 * TUT_CONCERT_PITCH)
#define TUT_A1 (TUT_s35 * TUT_CONCERT_PITCH)
#define TUT_b1 (TUT_s34 * TUT_CONCERT_PITCH)
#define TUT_c2 (TUT_s33 * TUT_CONCERT_PITCH)
#define TUT_C2 (TUT_s32 * TUT_CONCERT_PITCH)
#define TUT_d2 (TUT_s31 * TUT_CONCERT_PITCH)
#define TUT_D2 (TUT_s30 * TUT_CONCERT_PITCH)
#define TUT_e2 (TUT_s29 * TUT_CONCERT_PITCH)
#define TUT_f2 (TUT_s28 * TUT_CONCERT_PITCH)
#define TUT_F2 (TUT_s27 * TUT_CONCERT_PITCH)
#define TUT_g2 (TUT_s26 * TUT_CONCERT_PITCH)
#define TUT_G2 (TUT_s25 * TUT_CONCERT_PITCH)
#define TUT_a2 (TUT_s24 * TUT_CONCERT_PITCH)
#define TUT_A2 (TUT_s23 * TUT_CONCERT_PITCH)
#define TUT_b2 (TUT_s22 * TUT_CONCERT_PITCH)
#define TUT_c3 (TUT_s21 * TUT_CONCERT_PITCH)
#define TUT_C3 (TUT_s20 * TUT_CONCERT_PITCH)
#define TUT_d3 (TUT_s19 * TUT_CONCERT_PITCH)
#define TUT_D3 (TUT_s18 * TUT_CONCERT_PITCH)
#define TUT_e3 (TUT_s17 * TUT_CONCERT_PITCH)
#define TUT_f3 (TUT_s16 * TUT_CONCERT_PITCH)
#define TUT_F3 (TUT_s15 * TUT_CONCERT_PITCH)
#define TUT_g3 (TUT_s14 * TUT_CONCERT_PITCH)
#define TUT_G3 (TUT_s13 * TUT_CONCERT_PITCH)
#define TUT_a3 (TUT_s12 * TUT_CONCERT_PITCH)
#define TUT_A3 (TUT_s11 * TUT_CONCERT_PITCH)
#define TUT_b3 (TUT_s10 * TUT_CONCERT_PITCH)
#define TUT_c4 (TUT_s9 * TUT_CONCERT_PITCH)
#define TUT_C4 (TUT_s8 * TUT_CONCERT_PITCH)
#define TUT_d4 (TUT_s7 * TUT_CONCERT_PITCH)
#define TUT_D4 (TUT_s6 * TUT_CONCERT_PITCH)
#define TUT_e4 (TUT_s5 * TUT_CONCERT_PITCH)
#define TUT_f4 (TUT_s4 * TUT_CONCERT_PITCH)
#define TUT_F4 (TUT_s3 * TUT_CONCERT_PITCH)
#define TUT_g4 (TUT_s2 * TUT_CONCERT_PITCH)
#define TUT_G4 (TUT_s1 * TUT_CONCERT_PITCH)
#define TUT_a4 TUT_CONCERT_PITCH
#define TUT_A4 (TUT_S1 * TUT_CONCERT_PITCH)
#define TUT_b4 (TUT_S2 * TUT_CONCERT_PITCH)
#define TUT_c5 (TUT_S3 * TUT_CONCERT_PITCH)
#define TUT_C5 (TUT_S4 * TUT_CONCERT_PITCH)
#define TUT_d5 (TUT_S5 * TUT_CONCERT_PITCH)
#define TUT_D5 (TUT_S6 * TUT_CONCERT_PITCH)
#define TUT_e5 (TUT_S7 * TUT_CONCERT_PITCH)
#define TUT_f5 (TUT_S8 * TUT_CONCERT_PITCH)
#define TUT_F5 (TUT_S9 * TUT_CONCERT_PITCH)
#define TUT_g5 (TUT_S10 * TUT_CONCERT_PITCH)
#define TUT_G5 (TUT_S11 * TUT_CONCERT_PITCH)
#define TUT_a5 (TUT_S12 * TUT_CONCERT_PITCH)
#define TUT_A5 (TUT_S13 * TUT_CONCERT_PITCH)
#define TUT_b5 (TUT_S14 * TUT_CONCERT_PITCH)
#define TUT_c6 (TUT_S15 * TUT_CONCERT_PITCH)
#define TUT_C6 (TUT_S16 * TUT_CONCERT_PITCH)
#define TUT_d6 (TUT_S17 * TUT_CONCERT_PITCH)
#define TUT_D6 (TUT_S18 * TUT_CONCERT_PITCH)
#define TUT_e6 (TUT_S19 * TUT_CONCERT_PITCH)
#define TUT_f6 (TUT_S20 * TUT_CONCERT_PITCH)
#define TUT_F6 (TUT_S21 * TUT_CONCERT_PITCH)
#define TUT_g6 (TUT_S22 * TUT_CONCERT_PITCH)
#define TUT_G6 (TUT_S23 * TUT_CONCERT_PITCH)
#define TUT_a6 (TUT_S24 * TUT_CONCERT_PITCH)
#define TUT_A6 (TUT_S25 * TUT_CONCERT_PITCH)
#define TUT_b6 (TUT_S26 * TUT_CONCERT_PITCH)
#define TUT_c7 (TUT_S27 * TUT_CONCERT_PITCH)
#define TUT_C7 (TUT_S28 * TUT_CONCERT_PITCH)
#define TUT_d7 (TUT_S29 * TUT_CONCERT_PITCH)
#define TUT_D7 (TUT_S30 * TUT_CONCERT_PITCH)
#define TUT_e7 (TUT_S31 * TUT_CONCERT_PITCH)
#define TUT_f7 (TUT_S32 * TUT_CONCERT_PITCH)
#define TUT_F7 (TUT_S33 * TUT_CONCERT_PITCH)
#define TUT_g7 (TUT_S34 * TUT_CONCERT_PITCH)
#define TUT_G7 (TUT_S35 * TUT_CONCERT_PITCH)
#define TUT_a7 (TUT_S36 * TUT_CONCERT_PITCH)
#define TUT_A7 (TUT_S37 * TUT_CONCERT_PITCH)
#define TUT_b7 (TUT_S38 * TUT_CONCERT_PITCH)
#define TUT_c8 (TUT_S39 * TUT_CONCERT_PITCH)
#define TUT_C8 (TUT_S40 * TUT_CONCERT_PITCH)
#define TUT_d8 (TUT_S41 * TUT_CONCERT_PITCH)
#define TUT_D8 (TUT_S42 * TUT_CONCERT_PITCH)
#define TUT_e8 (TUT_S43 * TUT_CONCERT_PITCH)
#define TUT_f8 (TUT_S44 * TUT_CONCERT_PITCH)
#define TUT_F8 (TUT_S45 * TUT_CONCERT_PITCH)
#define TUT_g8 (TUT_S46 * TUT_CONCERT_PITCH)
#define TUT_G8 (TUT_S47 * TUT_CONCERT_PITCH)
#define TUT_a8 (TUT_S48 * TUT_CONCERT_PITCH)
#define TUT_A8 (TUT_S49 * TUT_CONCERT_PITCH)
#define TUT_b8 (TUT_S50 * TUT_CONCERT_PITCH)

#endif

#define TUT_NUM_ELEMS(A) \
	(sizeof(A)/sizeof(*(A)))

#define TUT_OFFSET_OF(s,memb) \
	((size_t)((char *)&((s *)0)->memb - (char *)0))

#define TUT_SEQUENCE(SEQUENCE, SYMBOL_TYPE, ...) for (struct {int index; SYMBOL_TYPE symbol;} SEQUENCE = {0}; ((SEQUENCE).symbol=(__VA_ARGS__)[((SEQUENCE).index)]); ++(SEQUENCE).index)

#define TUT_INSTRUMENT(name) \
	float name(float *samples, int num_samples, float frequency, float duration, double at, float volume) 
typedef TUT_INSTRUMENT(Tut_Instrument);

#define TUT_SINE_MEAN_MAG 0.637
#define TUT_TRIANGLE_MEAN_MAG 0.5
#define TUT_SQUARE_MEAN_MAG 1

double tut_wave_sine(double v) {
	v = sin(TUT_TAU * v);
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

	// if (v < 0.45) {
	//  v = 1;
	// }
	// else if (v < 0.5) {
	//  v = 1 - (v-0.45)/0.05;
	// }
	// else if (v < 0.55) {
	//  v = (v-0.5)/0.05;
	// }
	// else {
	//  v = 0;
	// }

	// v = v*2 - 1;

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

static float tut_envelope(float t, float *envelope, int num_points) {

	
	// Example:
	//
	// float envelope[] = {
	//     0,    0,
	//     0.01, 1,
	//     1,    0,
	// };

	// amplitude = tut_envelope(t, envelope, 3);
	
	
	float min_t = envelope[0];
	float min_v = envelope[1];
	float max_t;
	float max_v;

	for (int i = 2; i < num_points; i += 2) {
		max_t = envelope[i];
		max_v = envelope[i+1];
		if (t < max_t) {
			return min_v + ((t-min_t)/(max_t-min_t))*(max_v-min_v);
		}
		min_t = max_t;
		min_v = max_v;
	}

	return max_v;
}

typedef enum Tut_Opcode {
	TUT_OP_NONE = 0,
	TUT_OP_INSTRUMENT,
	TUT_OP_VOLUME,
	TUT_OP_SUB_TIMELINE,
	TUT_OP_PLAY,
	Tut_Opcode__COUNT
} Tut_Opcode;

typedef struct Tut_Op_Common {
	Tut_Opcode opcode;
	uint32_t sequence_number;
} Tut_Op_Common;

typedef struct Tut_Op_Play {
	Tut_Op_Common common;
	float frequency;
	float duration;
} Tut_Op_Play;

typedef struct Tut_Op_Instrument {
	Tut_Op_Common common;
	Tut_Instrument *instrument;
} Tut_Op_Instrument;

typedef struct Tut_Op_Volume {
	Tut_Op_Common common;
	float volume;
} Tut_Op_Volume;

struct Tut_Timeline;

typedef struct Tut_Op_Sub_Timeline {
	Tut_Op_Common common;
	struct Tut_Timeline *timeline;
} Tut_Op_Sub_Timeline;

typedef union Tut_Op {
	Tut_Op_Common common;
	Tut_Op_Play play;
	Tut_Op_Instrument instrument;
	Tut_Op_Volume volume;
	Tut_Op_Sub_Timeline sub_timeline;
} Tut_Op;

typedef struct Tut_Time_Op {
	double at;
	Tut_Op op;
} Tut_Time_Op;

typedef struct Tut_Timeline {
	double duration;

	size_t ops_capacity;
	uint64_t end_op_index;
	Tut_Time_Op *ops;

	size_t sample_capacity;
	uint64_t end_sample_index;
	float *samples;
} Tut_Timeline;

static TUT_INSTRUMENT(tut_default_instrument) {
	//(float *samples, int num_samples, float frequency, float duration, float at, float volume)

	(void)volume;

	for (int i = 0; i < num_samples; ++i) {
		float t = ((float)i/(float)num_samples);
		float signal = tut_wave_triangle(frequency * (at + t*duration));
		const float attack = 0.01;
		const float release = 0.5;
		signal *= 0.8;
		if (t < attack) {
			signal *= t/attack;
		}
		else if (t > release) {
			signal *= (1-(t-release)/(1-release));
		}
		samples[i] = signal;
	}

	return 0;
}

typedef struct Tut_Global_State {
	Tut_Timeline *timeline;
	double time_scale;
	double at;
	uint32_t sample_rate;
	uint32_t sequence_number;
} Tut_Global_State;

static Tut_Global_State tut_state = {
	.sample_rate = 44100,
	.time_scale = 1,
};

static inline double tut_at(void) {
	return tut_state.at / tut_state.time_scale;
}

static inline double tut_to(double at) {
	at *= tut_state.time_scale;
	return (tut_state.at = at);
}

static inline double tut_advance(double duration) {
	duration *= tut_state.time_scale;
	return (tut_state.at += duration);
}

static inline double tut_time_scale(double time_scale) {
	double old = tut_state.time_scale;
	tut_state.time_scale = time_scale;
	return old;
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

		void *new = realloc(tl->ops, new_ops_capacity * sizeof(tl->ops[0]));
		assert(new != NULL);


		tl->ops = new;
		tl->ops_capacity = new_ops_capacity;
	}

	tl->ops[tl->end_op_index++] = (Tut_Time_Op){tut_state.at, op};
}

static inline double tut_play(float frequency, float duration) {
	duration *= tut_state.time_scale;

	if (tut_state.timeline->duration < tut_state.at + duration) {
		tut_state.timeline->duration = tut_state.at + duration;
	}

	tut_push_op((Tut_Op){
		.play={
			.common={TUT_OP_PLAY, tut_state.sequence_number++},
			.frequency=frequency,
			.duration=(float)duration,
		}
	});

    return tut_state.at;
}

static inline float tut_play_advance(float frequency, double duration) {
	tut_play(frequency, duration);
	return tut_advance(duration);
}

static inline void tut_volume(float volume) {
	tut_push_op((Tut_Op){
		.volume={
			.common={TUT_OP_VOLUME, tut_state.sequence_number++},
			.volume=volume,
		}
	});
}

static inline void tut_instrument(Tut_Instrument *instrument) {
	if (!instrument) {
		instrument = tut_default_instrument;
	}
	tut_push_op((Tut_Op){
		.instrument={
			.common={TUT_OP_INSTRUMENT, tut_state.sequence_number++},
			.instrument=instrument,
		}
	});
}

static inline void tut_play_timeline(Tut_Timeline *timeline) {

	if (tut_state.timeline->duration < tut_state.at + timeline->duration) {
		tut_state.timeline->duration = tut_state.at + timeline->duration;
	}

	tut_push_op((Tut_Op){
		.sub_timeline={
			.common={TUT_OP_SUB_TIMELINE, tut_state.sequence_number++},
			.timeline=timeline,
		}
	});
}


static inline float tut_play_timeline_advance(Tut_Timeline *timeline) {

	tut_play_timeline(timeline);

	// float duration = (float)timeline->end_sample_index / (float)tut_state.sample_rate;

	return tut_advance(timeline->duration);
}

static inline void tut_add_samples(Tut_Timeline *tl, double at, float *samples, size_t num_samples, float factor) {

	size_t start_sample_index = (size_t)(tut_max(0, at) * tut_state.sample_rate);
	size_t end_sample_index = start_sample_index + num_samples;

	if (end_sample_index >= tl->sample_capacity) {

		size_t new_sample_capacity = (tl->sample_capacity != 0) ? 2*tl->sample_capacity : tut_state.sample_rate;

		while (new_sample_capacity < end_sample_index) {
			new_sample_capacity *= 2;
		}

		void *new = realloc(tl->samples, new_sample_capacity * sizeof(tl->samples[0]));
		assert(new != NULL);

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

void tut_normalize_samples(Tut_Timeline *tl, float factor) {
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
		tl->samples[i] *= factor/max_amplitude;
	}
}

static int _tut_op_time_compare (const void * _a, const void * _b) {
	const Tut_Time_Op *a = _a;
	const Tut_Time_Op *b = _b;

	if (a->at == b->at) {
		return a->op.common.sequence_number - b->op.common.sequence_number;
	}
	else {
		return (a->at < b->at) ? -1 : 1;
	}
}

static void tut_gen_samples(Tut_Timeline *timeline) {
	if (timeline->samples != NULL) {
		return;
	}

	qsort(timeline->ops, timeline->end_op_index, sizeof(timeline->ops[0]), _tut_op_time_compare);
	
	float volume = 1;
	Tut_Instrument *instrument = tut_default_instrument;

	for (uint64_t op_index = 0; op_index < timeline->end_op_index; ++op_index) {

		Tut_Time_Op time_op = timeline->ops[op_index];

		double at = time_op.at;
		Tut_Op op = time_op.op;

		switch (op.common.opcode) {
			case TUT_OP_SUB_TIMELINE: {
				tut_gen_samples(op.sub_timeline.timeline);
				assert(op.sub_timeline.timeline->samples);
				tut_add_samples(timeline, at, op.sub_timeline.timeline->samples, op.sub_timeline.timeline->end_sample_index, volume);
			}
			break;
			case TUT_OP_VOLUME: {
				volume = op.volume.volume;
			}
			break;
			case TUT_OP_PLAY: {
				int samples_per_duration = (int)(op.play.duration * tut_state.sample_rate);

				float *tmp_samples = calloc(samples_per_duration, sizeof(*tmp_samples));
				assert(tmp_samples);

				float offset = instrument(tmp_samples, samples_per_duration, op.play.frequency, op.play.duration, at, volume);

				tut_add_samples(timeline, at + offset, tmp_samples, (size_t)samples_per_duration, volume);
				free(tmp_samples);
			}
			break;
			case TUT_OP_INSTRUMENT: {
				instrument = op.instrument.instrument;
			}
			break;
			default: {
				assert(!"Invalid default case");
			}
		}
	}
}

static void tut_save_timeline_as_wave_file(Tut_Timeline *tl, FILE *file_handle) {

	#define four_chars(s) (uint32_t)((s[3]<<24) | (s[2]<<16) | (s[1]<<8) | s[0])

	typedef struct Wav_Header {
		// RIFF Header
		uint32_t riff_header; // Contains "RIFF"
		uint32_t wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
		
		// Format Header
		uint32_t wave_header; // Contains "WAVE"
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

	tut_gen_samples(tl);

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