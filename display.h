#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

SDL_Window* DISPLAY_window;
SDL_GLContext DISPLAY_glContext;

void DISPLAY_makeDisplay(int width, int height, char* title);
void DISPLAY_disposeDisplay();

void DISPLAY_clearDisplay(float r, float g, float b, float a);
void DISPLAY_updateDisplay();
void DISPLAY_resizeDisplay(int width, int height);
bool DISPLAY_isDisplayClosed();
int DISPLAY_getDisplayWidth();
int DISPLAY_getDisplayHeight();

#endif // DISPLAY_H_INCLUDED
