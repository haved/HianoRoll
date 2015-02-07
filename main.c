#include "includes.h"

AudioCallbackArray callbackArray;

int main()
{
    if(AP_Init())
        return 1;

    DISPLAY_makeDisplay(800, 600, "HianoRoll");

    UI_init();

    callbackArray.amount = 1;
    callbackArray.callbacks[0] = AP_squareWaveCallback;
    callbackArray.freqCounters[0] = 0;
    callbackArray.frequencies[0] = 440;
    callbackArray.volumes[0] = 10000;
    callbackArray.sampleRates[0] = 44100;

    AP_startPlayingAudio(&callbackArray);

    SDL_Delay(4000);
    AP_stopPlaying();

    AP_playExampleSound();

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

    puts("Tryingtoquit!");
    SDL_Quit();
    puts("Program exited properly. SDL_Quit();");
    return 0;
}

void printInt(int i)
{
    char tmp[32];
    snprintf(tmp, sizeof tmp, "%d", i);
    puts(tmp);
}
