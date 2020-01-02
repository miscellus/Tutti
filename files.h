#ifndef FILES_H
#define FILES_H

#include "voice_functions.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>

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

#if 0
static void SaveWaveFile(int16_t *samples, size_t num_samples, const char *FileName, uint32_t sample_rate) {
    size_t total_file_size = sizeof(Wav_Header) + num_samples*sizeof(int16_t);
    
    Wav_Header wh;
    wh.riff_header = FourChars("RIFF");
    wh.wav_size = total_file_size - 8;
    wh.wave_header = FourChars("WAVE");

    wh.fmt_header = FourChars("fmt ");
    wh.fmt_chunk_size = 16;
    wh.audio_format = 1; // 1 for PCM
    wh.num_channels = 1;
    wh.sample_rate = sample_rate;
    wh.byte_rate = wh.sample_rate * wh.num_channels * sizeof(int16_t);
    wh.sample_alignment = wh.num_channels * sizeof(int16_t);
    wh.bit_depth = 8*sizeof(int16_t);
    wh.data_header = FourChars("data");
    wh.data_bytes = num_samples*sizeof(int16_t);

    FILE *file_handle = fopen(FileName, "wb");
    fwrite(&wh, sizeof(wh), 1, file_handle);
    fwrite(samples, sizeof(int16_t), num_samples, file_handle);
    fclose(file_handle);
}
#else
static void write_wave_file(FILE *file_handle, int16_t *samples, size_t num_samples, uint32_t sample_rate) {
    size_t total_file_size = sizeof(Wav_Header) + num_samples*sizeof(int16_t);
    
    Wav_Header wh;
    wh.riff_header = FourChars("RIFF");
    wh.wav_size = total_file_size - 8;
    wh.wave_header = FourChars("WAVE");

    wh.fmt_header = FourChars("fmt ");
    wh.fmt_chunk_size = 16;
    wh.audio_format = 1; // 1 for PCM
    wh.num_channels = 1;
    wh.sample_rate = sample_rate;
    wh.byte_rate = wh.sample_rate * wh.num_channels * sizeof(int16_t);
    wh.sample_alignment = wh.num_channels * sizeof(int16_t);
    wh.bit_depth = 8*sizeof(int16_t);
    wh.data_header = FourChars("data");
    wh.data_bytes = num_samples*sizeof(int16_t);

    fwrite(&wh, sizeof(wh), 1, file_handle);
    fwrite(samples, sizeof(int16_t), num_samples, file_handle);
}
#endif

void file_get_contents(const char *file_path, char **buffer, size_t *buffer_size) {
    
    FILE *file_handle = fopen(file_path, "rb");

    if (file_handle) {
        fseek(file_handle, 0, SEEK_END);
        *buffer_size = ftell(file_handle);
        rewind(file_handle);
        
        if (*buffer_size > 0) {
            *buffer = malloc(*buffer_size + 1);
            assert(*buffer);

            size_t AmountRead = fread(*buffer, 1, *buffer_size, file_handle);
            (*buffer)[*buffer_size] = '\0';

            assert(AmountRead == *buffer_size);
        }
        else {
            fprintf(stderr, "Invalid file size %d for file '%s'\n", (int)*buffer_size, file_path);
        }
    }
    else {
        fprintf(stderr, "Could not read file '%s'\n", file_path);
    }

    fclose(file_handle);
}

typedef uint16_t instrument_id;
typedef uint16_t channel_id;

typedef struct song_event {
    uint16_t Row;
    double Frequency;
    struct song_event *Next;
} song_event;

typedef struct {
    instrument_id InstrumentID;
    song_event *FirstEvent;
    song_event *LastEvent;
} song_channel;

typedef struct {
    double FrequencyFactor;
    double Amplitude; // NOTE(jakob): in range 0-1
} overtone;

typedef double (*voice_function)(double);

typedef struct {
    double Time;
    double Amplitude;
} amplitude_point;

typedef struct {
    voice_function VoiceFunction;
    uint8_t OvertoneCount;
    overtone Overtones[8];
    amplitude_point AmplitudeEnvolope[8];
    double Release;
} instrument;

typedef struct {
    char *OutFile;
    double Duration; // In seconds
    uint32_t BeatsPerMinute;
    uint32_t sample_rate;
    uint32_t RowsPerBeat;
    double MasterVolume;
    uint32_t num_channels;
    double SecondsPerRow;
    song_channel Channels[32];
    instrument Instruments[16];
} loaded_song;

typedef struct {
    char Chars[128];
} cell_buffer;

instrument InstrumentForChannel(loaded_song *Song, channel_id ChannelID) {
    assert(ChannelID < Song->num_channels);
    instrument_id InstrumentID = Song->Channels[ChannelID].InstrumentID;
    assert(InstrumentID < ArraySize(Song->Instruments));
    return Song->Instruments[InstrumentID];
}

static inline bool IsWhiteSpaceChar(char c) {
    return c <= ' ';
}

static inline bool IsNumericChar(char c) {
    return c >= '0' && c <= '9';
}

static inline bool IsLetterChar(char c) {
    return (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z');    
}

static inline bool CharIn(char c, const char *Chars) {
    while (*Chars != c) ++Chars;
    return *Chars != '\0';
}

static inline char LowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a'-'A';
    }
    return c;
}

void EatSpaces(char **At) {
    while (**At <= ' ' && **At != '\n') *At += 1;
}

bool CompareCanonical(char *Src, const char *Dst) {
    while (*Src && *Dst) {
        if (IsWhiteSpaceChar(*Src) || *Src == '_' || *Src == '-') {
            ++Src;
        }
        else if (LowerCase(*Src) != LowerCase(*Dst)) {
            return false;
        }
        else {
            ++Src;
            ++Dst;
        }
    }

    return *Src == '\0' && *Dst == '\0';
}

void MakeStringCanonical(char *Scan) {
    char *WriteTo = Scan;
    while (*Scan) {
        
        if (*Scan > ' ' && *Scan != '_') {
            if (*Scan >= 'A' && *Scan <= 'Z') {
                *Scan += 'a'-'A';
            }
            *WriteTo = *Scan;
            ++WriteTo;
        }
        ++Scan;
    }
    *WriteTo = '\0';
}

size_t GetCell(char **At, cell_buffer *buffer) {
    while (**At && ((**At <= ' ' && **At != '\n') || **At == '"')) {
        ++*At;
    }

    char *From = *At;
    char *LastNonSpace = *At;

    while (**At && **At != ',' && **At != '\n') {

        if (!IsWhiteSpaceChar(**At) && **At != '"') {
            LastNonSpace = *At + 1;
        }

        ++*At;
    }

    size_t Length = LastNonSpace - From;
    Length = Min(Length, sizeof(buffer->Chars) - 1);

    memcpy(buffer->Chars, From, Length);

    buffer->Chars[Length] = '\0';

    return Length;
}

void NextCell(char **At, uint32_t *Row, uint32_t *Column) {
    while (**At && **At != ',' && **At != '\n') {
        ++*At;
    }

    if (**At == ',') {
        ++*Column;
        ++*At;
    }
    else if (**At == '\n') {
        *Column = 0;
        ++*Row;
        ++*At;
    }
}

void LoadSongFile(const char *FileName, loaded_song *Song) {

    /**************************/
    /* Initialize Song Struct */
    /**************************/
    {
        char FileNamebuffer[1024];
        int OutFileNameLength = snprintf(FileNamebuffer, sizeof(FileNamebuffer), "%s.wav", FileName);
        assert(OutFileNameLength > 0);

        Song->OutFile = malloc(OutFileNameLength + 1);
        assert(Song->OutFile);

        memcpy(Song->OutFile, FileNamebuffer, OutFileNameLength + 1);
        Song->OutFile[OutFileNameLength] = '\0';
        
        Song->BeatsPerMinute = 120;
        Song->sample_rate = 44100;
        Song->RowsPerBeat = 1;
        Song->MasterVolume = 0.3;

        for (uint32_t i = 0; i < ArraySize(Song->Instruments); ++i) {
            Song->Instruments[i].VoiceFunction = SineWave;
        }
    }
    
    char *FileContents;
    size_t FileSize;

    file_get_contents(FileName, &FileContents, &FileSize);

    char *At = FileContents;

    uint32_t Column = 0;
    uint32_t Row = 0;

    instrument_id CurrentIntrument = 0;

    cell_buffer Setting = {0};
    cell_buffer Value = {0};

    while (At < (FileContents + FileSize)) {

        /******************/
        /* Parse Settings */
        /******************/
        if (Column == 0) {

            size_t SettingLength = GetCell(&At, &Setting);
            NextCell(&At, &Row, &Column);

            if (SettingLength == 0) {
                NextCell(&At, &Row, &Column); // Skip Column 1
                continue;
            }

            size_t ValueLength = GetCell(&At, &Value);
            
            // MakeStringCanonical(Setting.Chars);

            bool UnknownSetting = false;

            if (CompareCanonical(Setting.Chars, "bpm")) {
                Song->BeatsPerMinute = atoi(Value.Chars);
            }
            else if (CompareCanonical(Setting.Chars, "sample""rate")) {
                Song->sample_rate = atoi(Value.Chars);
            }
            else if (CompareCanonical(Setting.Chars, "rows""per""beat")) {
                Song->RowsPerBeat = atoi(Value.Chars);
            }
            else if (CompareCanonical(Setting.Chars, "instrument")) {
                CurrentIntrument = atoi(Value.Chars);
                fprintf(stderr, "Parsing Settings for instrument %d.\n", CurrentIntrument);
            }
            else if (CompareCanonical(Setting.Chars, "release")) {
                instrument *I = &Song->Instruments[CurrentIntrument];
                I->Release = atof(Value.Chars);
            }
            else if (CompareCanonical(Setting.Chars, "voice")) {
                instrument *I = &Song->Instruments[CurrentIntrument];
                
                if (CompareCanonical(Value.Chars, "sine"))
                    I->VoiceFunction = SineWave;
                else if (CompareCanonical(Value.Chars, "triangle"))
                    I->VoiceFunction = TriangleWave;
                else if (CompareCanonical(Value.Chars, "square"))
                    I->VoiceFunction = SquareWave;
                else if (CompareCanonical(Value.Chars, "saw"))
                    I->VoiceFunction = SawWave;
            }
            else if (CompareCanonical(Setting.Chars, "master""volume")) {
                Song->MasterVolume = atof(Value.Chars);
            }
            else if (CompareCanonical(Setting.Chars, "output""file")) {
                size_t Length = ValueLength + 1;
                Song->OutFile = malloc(Length);
                assert(Song->OutFile);
                memcpy(Song->OutFile, Value.Chars, Length);
            }
            else {
                fprintf(stderr, "Ignored unknown setting, \"%s = %s\"\n", Setting.Chars, Value.Chars);
                UnknownSetting = true;
            }

            if (!UnknownSetting) {
                fprintf(stderr, "SET: %s = %s;\n", Setting.Chars, Value.Chars);
            }
        }
        /***************/
        /* Parse Notes */
        /***************/
        else if (Row > 0) {

            cell_buffer Cell;
            song_event *Ev = calloc(1, sizeof(*Ev));
            // *Ev = (song_event){0};

            if (GetCell(&At, &Cell) > 0) {
                size_t Channel = Column - 2;
                assert(Channel < 16);

                Ev->Row = Row - 1;
                Ev->Frequency = NoteStringToFrequency(Cell.Chars);

                if (NULL == Song->Channels[Channel].FirstEvent) {
                    Song->Channels[Channel].FirstEvent = Ev;
                    Song->Channels[Channel].LastEvent = Ev;
                }
                else {
                    Song->Channels[Channel].LastEvent->Next = Ev;
                    Song->Channels[Channel].LastEvent = Ev;
                }
            }

            NextCell(&At, &Row, &Column);
        }
        /************************/
        /* Parse Instrument IDs */
        /************************/
        else if (Row == 0) {
            cell_buffer InstrumentIDBuf;

            if (GetCell(&At, &InstrumentIDBuf) > 0) {
                size_t Channel = Column - 2;
                ++Song->num_channels;
                Song->Channels[Channel].InstrumentID = atoi(InstrumentIDBuf.Chars);
            }
            NextCell(&At, &Row, &Column);
        }
        else {
            assert(false);
        }
    }

    Song->SecondsPerRow = 60.0 / (Song->BeatsPerMinute * Song->RowsPerBeat);
    Song->Duration = Song->SecondsPerRow*Row;
}

#endif