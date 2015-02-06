#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED

typedef struct
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

int AP_Init();

Sint16 sineWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
void sineWaveCallback(void* userData, Uint8* streamIn, int length);
//int startPlayingSineWave(SineWaveInfo* wave);
int AP_startPlayingSineWaves(SineWaveInfoArray* waves);
void AP_stopPlaying();

#endif // AUDIOPLAYER_H_INCLUDED
