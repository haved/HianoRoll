#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} Color;

void SET_color(Color* color, float r, float g, float b, float a);

void RENDER_setColorf(float r, float g, float b, float a);
void RENDER_setColor(Color c);
void RENDER_fillRect(float x, float y, float width, float height);

#endif // RENDERER_H_INCLUDED
