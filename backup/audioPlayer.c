#include "includes.h"

Sint16 sineWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    return (Sint16)(volume * sin(*freqCounter * 2 * PI/sampleRate));
}

void sineWaveCallback(void* userData, Uint8 *streamIn, int length)
{
    SineWaveInfo *wave = (SineWaveInfo *) userData;
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    for(int i = 0; i < len; i++)
    {
        stream[i] = sineWave(wave->volume, wave->frequency, wave->sampleRate, &wave->freqCounter);
    }
}

int startPlayingSineWaves(SineWaveInfoArray waves)
{
    //Cant't be used!!
    SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = *sineWaveCallback;
    desiredSpec.userdata = &waves;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;
}

int startPlayingSineWave(SineWaveInfo* wave)
{
    SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = *sineWaveCallback;
    desiredSpec.userdata = wave;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;
}

void stopPlaying()
{
    SDL_CloseAudio();
}

int InitAudioPlayer()
{
    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        printf("Failed to initialize the sound system with SDL_Init(SDL_INIT_AUDIO)!");
        return 1;
    }
    return 0;
}

/*#include "includes.h"

Sint16 sineWave(Sint16 volume, int frequency, int sampleRate, int* freqCounter)
{
    *freqCounter += frequency;
    return (Sint16)(volume * sin(*freqCounter * 2 * PI/sampleRate));
}

void sineWaveCallback(void* userData, Uint8 *streamIn, int length)
{
    SineWaveInfoArray *waveArray = (SineWaveInfoArray *) userData;
    printf("%d\n", (*waveArray).amount);
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    int i, j;
    for(i = 0; i < len; i++)
    {
        /-for(j = 0; j < waveArray->amount; j++)
        stream[i] += sineWave((waveArray->waves+j)->volume, (waveArray->waves+j)->frequency,
                             (waveArray->waves+j)->sampleRate, (waveArray->waves+j)->freqCounter);-/

    }


    /-SineWaveInfo *wave = (SineWaveInfo *) userData;
    int len = length/2;
    Sint16* stream = (Sint16*) streamIn;

    for(int i = 0; i < len; i++)
    {
        stream[i] = sineWave((*wave).volume, (*wave).frequency, (*wave).sampleRate, &(*wave).freqCounter);
    }-/
}

int startPlayingSineWaves(SineWaveInfoArray waves)
{
    SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = *sineWaveCallback;
    desiredSpec.userdata = &waves;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;
}

int startPlayingSineWave(SineWaveInfo* wave)
{
    SineWaveInfoArray wavesInfo;
    wavesInfo.waves = wave;
    wavesInfo.amount = 1;

    return startPlayingSineWaves(wavesInfo);

    /-SDL_AudioSpec desiredSpec;

    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 512;
    desiredSpec.callback = *sineWaveCallback;
    desiredSpec.userdata = wave;

    if(SDL_OpenAudio(&desiredSpec, NULL) < 0)
    {
        printf("Failed top play audio!\n");
        return 1;
    }

    SDL_PauseAudio(0);

    return 0;-/
}

void stopPlaying()
{
    SDL_CloseAudio();
}

int InitAudioPlayer()
{
    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        printf("Failed to initialize the sound system with SDL_Init(SDL_INIT_AUDIO)!");
        return 1;
    }
    return 0;
}
*/
