#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#define MAX_TRACKS 10

#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <math.h>

#include <stdbool.h>
#include <sys/types.h>

#include "display.h"
#include "audioPlayer.h"
#include "UI.h"
#include "renderer.h"
#include "input.h"

typedef struct{
    Sint16 (*instrument)(Sint16, int, int, int*);
} Track;

typedef struct
{
    Track tracks[MAX_TRACKS];
    int amount;
} TrackArray;

TrackArray trackArray;

void printInt(int i);

#define PI 3.14159265

#endif // INCLUDES_H_INCLUDED
