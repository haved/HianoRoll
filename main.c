#include "includes.h"

AudioCallbackArray callbackArray;

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

    puts("Trying to SDL_Quit();");
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
