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

int noteToFrequency(int note)
{
    return pow(2,note-49/12)*440;
}

bool isNoteBlack(int note)
{
    return (((note-4) % 12) < 5) ^ ((note%2)==0);
}

void AP_playExampleAudio()
{
    AudioCallbackArray callbackArray;

    callbackArray.amount = 1;
    callbackArray.callbacks[0] = AP_sineWaveCallback;
    callbackArray.freqCounters[0] = 0;
    callbackArray.frequencies[0] = 440;
    callbackArray.volumes[0] = 10000;
    callbackArray.sampleRates[0] = 44100;

    AP_startPlayingAudio(&callbackArray);

    SDL_Delay(4000);

    callbackArray.callbacks[0] = AP_squareWaveCallback;

    SDL_Delay(4000);

    callbackArray.callbacks[0] = AP_triangleWaveCallback;

    SDL_Delay(4000);

    callbackArray.callbacks[0] = AP_sineWaveCallback;

    SDL_Delay(4000);

    AP_stopPlaying();
}
