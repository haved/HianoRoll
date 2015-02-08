#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct{
    Sint16 (*instrument)(Sint16, int, int, int*);
    Color color;
} Track;

typedef struct
{
    Track tracks[MAX_TRACKS];
    int amount;
} TrackArray;

TrackArray trackArray;

void pollEvents();
void printInt(int i);

#endif // MAIN_H_INCLUDED
