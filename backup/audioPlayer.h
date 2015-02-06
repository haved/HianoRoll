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
    SineWaveInfo waves[10];
    int amount;
} SineWaveInfoArray;

int InitAudioPlayer();

Sint16 sineWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter);
void sineWaveCallback(void* userData, Uint8* streamIn, int length);
int startPlayingSineWave(SineWaveInfo* wave);
void stopPlaying();

#endif // AUDIOPLAYER_H_INCLUDED
