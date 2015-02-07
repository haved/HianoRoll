#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

typedef struct{
    int panY;
    int zoom;
} TracksRendererInfo;

typedef struct{
    Sint16 (*instrument)(Sint16, int, int, int*);
} Track;

void UI_init();
void UI_updateUI();
void UI_updateMiddleBar();
void UI_renderUI();
void UI_renderTracks(int y, int y2);

#endif // UI_H_INCLUDED
