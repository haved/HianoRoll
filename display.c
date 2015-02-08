#include "includes.h"

void DISPLAY_makeDisplay(int width, int height, char* title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    DISPLAY_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    DISPLAY_glContext = SDL_GL_CreateContext(DISPLAY_window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        printf("Failed to initialize GL/glew!\n");
    }

    DISPLAY_resizeDisplay(width, height);
}

void DISPLAY_disposeDisplay()
{
    SDL_GL_DeleteContext(DISPLAY_glContext);
    SDL_DestroyWindow(DISPLAY_window);
}

bool DISPLAY_closed;

void DISPLAY_updateDisplay()
{
    SDL_GL_SwapWindow(DISPLAY_window);
}

void DISPLAY_clearDisplay(float r, float g , float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

int DISPLAY_width;
int DISPLAY_height;
void DISPLAY_resizeDisplay(int width, int height)
{
    DISPLAY_width = width;
    DISPLAY_height = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW_MATRIX);
}

void DISPLAY_closeDisplay()
{
    DISPLAY_closed = true;
}

bool DISPLAY_isDisplayClosed()
{
    return DISPLAY_closed;
}

int DISPLAY_getDisplayWidth()
{
    return DISPLAY_width;
}

int DISPLAY_getDisplayHeight()
{
    return DISPLAY_height;
}
