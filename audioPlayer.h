#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED

typedef struct
{
    Sint16 (*callbacks[MAX_TRACKS])(Sint16, int, int, int*);
    Sint16 volumes[MAX_TRACKS];
    int frequencies[MAX_TRACKS];
    int freqCounters[MAX_TRACKS];
    int sampleRates[MAX_TRACKS];
    int amount;
} AudioCallbackArray;

int AP_Init();

Sint16 AP_sineWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
Sint16 AP_squareWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
Sint16 AP_triangleWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);

void audioCallback(void* userData, Uint8* stream, int length);
int AP_startPlayingAudio(AudioCallbackArray* callbacks);
void AP_stopPlaying();

int noteToFrequency(int note);
bool isNoteBlack(int note);

void AP_playExampleAudio();




/*typedef struct
{
    Sint16 volume;
    int frequency;
    int freqCounter;
    int sampleRate;
} SineWaveInfo;

typedef struct
{
    int amount;
    SineWaveInfo* waves[10];
} SineWaveInfoArray;

void AP_sineWaveArrayCallback(void* userData, Uint8* streamIn, int length);
int AP_startPlayingSineWaves(SineWaveInfoArray* waves);*/

#endif // AUDIOPLAYER_H_INCLUDED
