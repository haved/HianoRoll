#include "includes.h"

void RENDER_setColor(float r, float g, float b, float a)
{
    glColor4f(r,g,b,a);
}

void RENDER_fillRect(float x, float y, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x,  y);
    glVertex2f(x,  y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y);
    glEnd();
}
