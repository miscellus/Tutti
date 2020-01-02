#ifndef TUTTI
#define TUTTI

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <malloc.h>
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


typedef enum Tut_Export_File_Type {
    TUT_FILE_WAV = 0,
} Tut_Export_File_Type;

typedef enum Tut_Instruction_Kind {
    TUT_INS_NONE = 0,
    TUT_INS_PLAY = 1,
    TUT_INS_REST = 2,
    TUT_INS_DURATION = 3,
    TUT_INS_LAST = TUT_INS_DURATION,
} Tut_Instruction_Kind;

typedef struct Tut_Instruction {
    Tut_Instruction_Kind kind;

    union {
        struct {
            double frequency;
        } play;
        double duration;
    } u;
} Tut_Instruction;

typedef struct Tut_Channel {
    double duration;
    uintptr_t next_instruction_offset;
    size_t instruction_stream_capacity;
    uint8_t *instruction_stream;
} Tut_Channel;

typedef struct Tut_Song {
    struct {
        int channel_index;
    } current;
    int16_t *samples;
    size_t num_samples;
    size_t used_samples;
    uint32_t sample_rate;
    Tut_Channel channels[2];
} Tut_Song;

static Tut_Song *global_song;

static inline void tut_print_instruction(Tut_Instruction ins) {
    switch(ins.kind){
        case TUT_INS_PLAY:
            fprintf(stderr, "Ins: {.kind=PLAY,.play={.frequency=%f}}\n", ins.u.play.frequency);
            break;
        case TUT_INS_REST:
            fprintf(stderr, "Ins: {.kind=REST}\n");
            break;
        case TUT_INS_DURATION:
            fprintf(stderr, "Ins: {.kind=DURATION,.duration=%f}\n", ins.u.duration);
            break;
        default:
            fprintf(stderr, "Ins: {.kind=UNKNOWN (%d)}\n", ins.kind);
    }
}

Tut_Song tut_make_song(void) {
    Tut_Song result = {0};

    result.sample_rate = 44100;
    result.num_samples = result.sample_rate * 60 * 60;
    result.samples = calloc(1, result.num_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < tut_static_array_len(result.channels); ++i) {
        Tut_Channel *channel = &result.channels[i];
        *channel = (Tut_Channel){0};
        
        channel->duration = 0.5;
        size_t cap = 128 * sizeof(Tut_Instruction);
        channel->instruction_stream_capacity = cap;
        channel->instruction_stream = malloc(cap);
        assert(channel->instruction_stream);
    }

    return result;
}

void tut_set_song(Tut_Song *song) {
    global_song = song;
}

static inline size_t get_instruction_size(Tut_Instruction ins) {
    size_t result = tut_offset_of(Tut_Instruction, u);

    switch(ins.kind) {
    case TUT_INS_PLAY:
        result += sizeof(ins.u.play); break;
    case TUT_INS_REST:
        break;
    case TUT_INS_DURATION:
        result += sizeof(ins.u.duration); break;
    default:
        fprintf(stderr, "Ins Kind: %d\n", ins.kind);
        assert(false);
    }

    // fprintf(stderr, "ins.kind %d, size: %d\n", ins.kind, (int)result);
    return result;
}

void tut_push_instruction(Tut_Instruction ins) {

    Tut_Channel *channel = &global_song->channels[global_song->current.channel_index];

    size_t ins_size = get_instruction_size(ins);
    uintptr_t next_instruction_offset = channel->next_instruction_offset;
    // fprintf(stderr, "next_instruction_offset %"PRIxPTR", new_next_instruction_offset %"PRIxPTR"\n", next_instruction_offset, new_next_instruction_offset);
    size_t instruction_stream_capacity = channel->instruction_stream_capacity;

    if (next_instruction_offset + ins_size >= instruction_stream_capacity) {
        void *new = realloc(channel->instruction_stream, 2*instruction_stream_capacity);
        assert(new != NULL);

        if (new != channel->instruction_stream) {
            fprintf(stderr, "realloc !\n");
        }

        channel->instruction_stream = new;
        channel->instruction_stream_capacity *= 2;
    }

    tut_print_instruction(ins);
    Tut_Instruction *insert_at = (Tut_Instruction *)(channel->instruction_stream + next_instruction_offset);
    *insert_at = ins;
    tut_print_instruction(*insert_at);
    channel->next_instruction_offset += ins_size;

}

void tut_play(double frequency) {

    Tut_Instruction ins = {
        .kind = TUT_INS_PLAY,
        .u.play = {.frequency = frequency},
    };

    tut_push_instruction(ins);
}

void tut_rest(void) {

    Tut_Instruction ins = {
        .kind = TUT_INS_REST,
    };

    tut_push_instruction(ins);
}

void tut_duration(double duration) {
    Tut_Instruction ins = {
        .kind = TUT_INS_DURATION,
        .u.duration = duration,
    };

    tut_push_instruction(ins);
}

typedef struct Tut_Instruction_Iterator {
    Tut_Channel *channel;
    uint8_t *at;
} Tut_Instruction_Iterator;

Tut_Instruction_Iterator tut_instruction_iterator(Tut_Channel *channel) {
    Tut_Instruction_Iterator result = {
        .channel = channel,
        .at = channel->instruction_stream,
    };

    return result;
}

Tut_Instruction *tut_next_instruction(Tut_Instruction_Iterator *iter) {
    Tut_Instruction *result = (Tut_Instruction *)iter->at;

    if (result->kind == TUT_INS_NONE) {
        return NULL;
    }

    size_t size = get_instruction_size(*result);

    // fprintf(stderr, "##############size: %d\niter->at:%p, iter->at+size: %p\n", (int)size, iter->at, iter->at+size);
    iter->at += size;

    tut_print_instruction(*result);

    return result;
}

void tut_finalize_song(void) {
    // for (unsigned int i = 0; i < tut_static_array_len(global_song->channels); ++i) {
    Tut_Channel *channel = &global_song->channels[0];

    Tut_Instruction_Iterator iter = tut_instruction_iterator(channel);

    size_t sample_index = 0;
    int16_t *samples = global_song->samples;

    Tut_Instruction *ins = NULL;

    while ((ins = tut_next_instruction(&iter))) {

        int samples_per_duration = (int)(channel->duration * global_song->sample_rate);

        switch (ins->kind) {
        case TUT_INS_PLAY: {
            tut_print_instruction(*ins);
            for (int i = 0; i < samples_per_duration; ++i) {
                double time = (double)sample_index / (double)global_song->sample_rate;
                double signal = tut_wave_sine(ins->u.play.frequency * time);
                signal *= 0.6;
                samples[sample_index++] = (int16_t)(signal * 0x8000);
            }
        } break;
        case TUT_INS_REST: {
            for (int i = 0; i < samples_per_duration; ++i) {
                samples[sample_index++] = 0;
            }
        } break;
        case TUT_INS_DURATION: {
            channel->duration = ins->u.duration;
        } break;
        default: {
            assert(ins->kind <= TUT_INS_LAST);
            break;
        }
        }
    }

    global_song->used_samples = sample_index;
}

static void tut_write_wave_file(FILE *file_handle) {
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

    int16_t *samples = global_song->samples;
    size_t num_samples = global_song->used_samples;
    uint32_t sample_rate = global_song->sample_rate;

    size_t total_file_size = sizeof(Wav_Header) + num_samples*sizeof(int16_t);
    
    Wav_Header wh;
    wh.riff_header = four_chars("RIFF");
    wh.wav_size = total_file_size - 8;
    wh.wave_header = four_chars("WAVE");

    wh.fmt_header = four_chars("fmt ");
    wh.fmt_chunk_size = 16;
    wh.audio_format = 1; // 1 for PCM
    wh.num_channels = 1;
    wh.sample_rate = sample_rate;
    wh.byte_rate = wh.sample_rate * wh.num_channels * sizeof(int16_t);
    wh.sample_alignment = wh.num_channels * sizeof(int16_t);
    wh.bit_depth = 8*sizeof(int16_t);
    wh.data_header = four_chars("data");
    wh.data_bytes = num_samples*sizeof(int16_t);

    fwrite(&wh, sizeof(wh), 1, file_handle);
    fwrite(samples, sizeof(int16_t), num_samples, file_handle);

    #undef four_chars
}


#endif