#include "includes.h"

int INPUT_mouseX, INPUT_mouseY;
int INPUT_mouseScroll;
bool INPUT_leftMouseDown;
bool INPUT_rightMouseDown;
bool INPUT_wasLeftMouseDownPrev;
bool INPUT_wasRightMouseDownPrev;

void INPUT_update()
{
    INPUT_wasLeftMouseDownPrev = INPUT_leftMouseDown;
    INPUT_wasRightMouseDownPrev = INPUT_rightMouseDown;
    SDL_PumpEvents();
    INPUT_mouseScroll = 0;
    Uint32 state = SDL_GetMouseState(&INPUT_mouseX, &INPUT_mouseY);
    INPUT_leftMouseDown = state & SDL_BUTTON(SDL_BUTTON_LEFT);
    INPUT_rightMouseDown = state & SDL_BUTTON(SDL_BUTTON_RIGHT);
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

bool INPUT_isLeftMouseDown()
{
    return INPUT_leftMouseDown;
}

bool INPUT_isRightMouseDown()
{
    return INPUT_rightMouseDown;
}

bool INPUT_wasLeftMouseDown()
{
    return INPUT_wasLeftMouseDownPrev;
}

bool INPUT_wasRightMouseDown()
{
    return INPUT_wasRightMouseDownPrev;
}

int INPUT_getMouseScroll()
{
    return INPUT_mouseScroll;
}
