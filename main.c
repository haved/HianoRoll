#include "includes.h"

int main()
{
    if(AP_Init())
        return 1;

    DISPLAY_makeDisplay(800, 600, "HianoRoll");

    UI_init();

    while(!DISPLAY_isDisplayClosed())
    {
        INPUT_update();
        UI_updateUI();
        DISPLAY_clearDisplay(1.0f, 0.5f, 0.2f, 1.0f);
        UI_renderUI();
        DISPLAY_updateDisplay();
        SDL_Delay(8);
    }

    DISPLAY_disposeDisplay();

    SDL_Quit();
    printf("Program exited properly. SDL_Quit();\n");
    return 0;
}

void playExampleSound()
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

    SDL_Delay(10000);

    AP_stopPlaying();
}
