#include "includes.h"

int main()
{
    if(AP_Init()) //AP is the audio player
        return 1;

    DISPLAY_makeDisplay(800, 600, "HianoRoll");

    UI_init();

    while(!DISPLAY_isDisplayClosed())
    {
        INPUT_update();
        pollEvents();
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

void pollEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
        switch(e.type)
        {
            case SDL_QUIT: DISPLAY_closeDisplay(); break;
            case SDL_WINDOWEVENT: if(e.window.event == SDL_WINDOWEVENT_RESIZED) DISPLAY_resizeDisplay(e.window.data1, e.window.data2); break;
            case SDL_MOUSEWHEEL:
                INPUT_setMouseScroll(e.wheel.y); break;
            default: break;
        }
}

void printInt(int i)
{
    char tmp[32];
    snprintf(tmp, sizeof tmp, "%d", i);
    puts(tmp);
}
