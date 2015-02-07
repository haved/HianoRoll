#include "includes.h"

Sint16 AP_sineWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    return (Sint16)(volume * sin(*freqCounter * 2 * PI/sampleRate));
}

Sint16 AP_squareWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    if((*freqCounter%sampleRate)>sampleRate/2)
        return volume;
    else
        return -volume;
}

Sint16 AP_triangleWaveCallback(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    int val = 4 * abs((*freqCounter % sampleRate) - sampleRate/2) - sampleRate;
    *freqCounter += frequency;
    return (Sint16)((volume * val)/sampleRate);
}

void audioCallback(void* userData, Uint8 *streamIn, int length)
{
    AudioCallbackArray* callbackArray = (AudioCallbackArray *) userData;
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    for(int i = 0; i < len; i++)
    {
        stream[i] = 0;
        for(int j = 0; j < callbackArray->amount; j++)
            stream[i] += (*(callbackArray->callbacks[j]))(callbackArray->volumes[j], callbackArray->frequencies[j], callbackArray->sampleRates[j], &callbackArray->freqCounters[j]);
            printf("%d\n", stream[i]);
    }
}

int AP_startPlayingAudio(AudioCallbackArray* callbacks)
{
    SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = audioCallback;
    desiredSpec.userdata = callbacks;

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







/*void AP_sineWaveArrayCallback(void* userData, Uint8 *streamIn, int length)
{
    SineWaveInfoArray* waveArray = (SineWaveInfoArray *) userData;
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    for(int i = 0; i < len; i++)
    {
        stream[i] = 0;
        for(int j = 0; j < waveArray->amount; j++)
            stream[i] += AP_sineWaveCallback(waveArray->waves[j]->volume, waveArray->waves[j]->frequency, waveArray->waves[j]->sampleRate, &waveArray->waves[j]->freqCounter);
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
    desiredSpec.callback = AP_sineWaveArrayCallback;
    desiredSpec.userdata = waves;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;
}

void AP_playExampleSound()
{
    SineWaveInfoArray waves;
    SineWaveInfoArray* waveArray = &waves;
    SineWaveInfo wave;
    wave.volume = 10000;
    wave.sampleRate = 44100;
    wave.frequency = 440;
    wave.freqCounter = 0;

    SineWaveInfo wave2 = wave;
    wave2.frequency = 554.37f;

    SineWaveInfo wave3 = wave;
    wave3.frequency = 659.25f;

    waveArray->amount=3;
    waveArray->waves[0]=&wave;
    waveArray->waves[1]=&wave2;
    waveArray->waves[2]=&wave3;

    AP_startPlayingSineWaves(waveArray);

    SDL_Delay(4000);

    AP_stopPlaying();
}*/
