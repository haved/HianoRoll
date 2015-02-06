#include "includes.h"

int INPUT_mouseX, INPUT_mouseY;
bool INPUT_mouseDown;

void INPUT_update()
{
    SDL_PumpEvents();
    INPUT_mouseDown = SDL_GetMouseState(&INPUT_mouseX, &INPUT_mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
    puts(INPUT_mouseDown ? "true" : "false");
}

int INPUT_getMouseX()
{
    return INPUT_mouseX;
}

int INPUT_getMouseY()
{
    return INPUT_mouseY;
}

bool INPUT_isMouseDown()
{
    return INPUT_mouseDown;
}
