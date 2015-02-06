#include "includes.h"

Sint16 sineWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    return (Sint16)(volume * sin(*freqCounter * 2 * PI/sampleRate));
}

Sint16 squareWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    if(sin(*freqCounter * 2 * PI/sampleRate)>0)
        return volume;
    else
        return -volume;
}

void sineWaveCallback(void* userData, Uint8 *streamIn, int length)
{
    SineWaveInfoArray* waveArray = (SineWaveInfoArray *) userData;
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    for(int i = 0; i < len; i++)
    {
        stream[i] = 0;
        for(int j = 0; j < waveArray->amount; j++)
            stream[i] += sineWave(waveArray->waves[j]->volume, waveArray->waves[j]->frequency, waveArray->waves[j]->sampleRate, &waveArray->waves[j]->freqCounter);
    }
}

int AP_startPlayingSineWaves(SineWaveInfoArray* waves)
{
    SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = *sineWaveCallback;
    desiredSpec.userdata = waves;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;
}

void AP_stopPlaying()
{
    SDL_CloseAudio();
}

int AP_Init()
{
    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        printf("Failed to initialize the sound system with SDL_Init(SDL_INIT_AUDIO)!");
        return 1;
    }
    return 0;
}
