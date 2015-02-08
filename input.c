#include "includes.h"

int INPUT_mouseX, INPUT_mouseY;
int INPUT_mouseScroll;
bool INPUT_mouseDown;

void INPUT_update()
{
    SDL_PumpEvents();
    INPUT_mouseDown = SDL_GetMouseState(&INPUT_mouseX, &INPUT_mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

void INPUT_setMouseScroll(int verticalScroll)
{
    INPUT_mouseScroll = verticalScroll;
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

int INPUT_getMouseScroll()
{
    return INPUT_mouseScroll;
}
