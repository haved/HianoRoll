#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#define MIN_NOTE 13
#define MAX_NOTE 73
#define A_NOTE 49

typedef struct{
    int panY;
    int zoom;
} TracksRendererInfo;

void UI_init();
void UI_updateUI();
void UI_updateMiddleBar();
void UI_renderUI();
void UI_renderTracks(int y, int y2, TracksRendererInfo info);

#endif // UI_H_INCLUDED
