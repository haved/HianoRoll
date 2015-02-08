#include "includes.h"

void SET_color(Color* color, float r, float g, float b, float a)
{
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void RENDER_setColorf(float r, float g, float b, float a)
{
    glColor4f(r,g,b,a);
}

void RENDER_setColor(Color c)
{
    glColor4f(c.r, c.g, c.b, c.a);
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
