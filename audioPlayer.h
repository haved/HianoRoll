#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED

typedef struct
{
    int (*callbacks[10])(Sint16, int, int, int*);
    Sint16 volumes[10];
    int frequencies[10];
    int freqCounters[10];
    int sampleRates[10];
    int amount;
} AudioCallbackArray;

int AP_Init();

Sint16 AP_sineWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
Sint16 AP_squareWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
Sint16 AP_triangleWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter);

void audioCallback(void* userData, Uint8* stream, int length);
int AP_startPlayingAudio(AudioCallbackArray* callbacks);
void AP_stopPlaying();


/*typedef struct
{
    int amount;
    SineWaveInfo* waves[10];
} SineWaveInfoArray;*/

#endif // AUDIOPLAYER_H_INCLUDED
