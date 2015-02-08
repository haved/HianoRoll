#include "includes.h"

#define MIDDLE_BAR_SIZE 6
#define TRACK_INFO_BAR_SIZE 180
#define KEY_COLOR_WIDTH 50

int UI_middleBar;
TracksRendererInfo topPanelRenderInfo;
TracksRendererInfo bottomPanelRenderInfo;

void UI_init()
{
    UI_middleBar = DISPLAY_getDisplayHeight() / 2;
    topPanelRenderInfo.zoom=2;
    bottomPanelRenderInfo.zoom=4;


    trackArray.amount = 2;
    SET_color(&trackArray.tracks[0].color, 0.3f, 0.3f, 0.9f, 1);
    SET_color(&trackArray.tracks[1].color, 0.3f, 0.9f, 0.3f, 1);
}

void UI_updateUI()
{
    UI_updateMiddleBar();
    if(INPUT_getMouseScroll()!=0)
        UI_handleScroll();
}

bool m_middleBarHeld;
bool m_prevTickMouseDown;
void UI_updateMiddleBar()
{
    if(INPUT_isMouseDown())
    {
        if(m_middleBarHeld)
        {
            UI_middleBar = INPUT_getMouseY();
        }
        else if(!m_prevTickMouseDown & (INPUT_getMouseY() >= (UI_middleBar-MIDDLE_BAR_SIZE)) & (INPUT_getMouseY() <= (UI_middleBar+MIDDLE_BAR_SIZE)))
        {
            m_middleBarHeld = true;
        }
    }
    else
        m_middleBarHeld = false;

    m_prevTickMouseDown = INPUT_isMouseDown();

    if(UI_middleBar > DISPLAY_getDisplayHeight()-MIDDLE_BAR_SIZE)
        UI_middleBar = DISPLAY_getDisplayHeight()-MIDDLE_BAR_SIZE;
}

void UI_handleScroll()
{
    if(INPUT_getMouseY()<UI_middleBar-MIDDLE_BAR_SIZE)
        topPanelRenderInfo.zoom += (INPUT_getMouseScroll()>0?1:-1);
    if(INPUT_getMouseY()>UI_middleBar+MIDDLE_BAR_SIZE)
        bottomPanelRenderInfo.zoom += (INPUT_getMouseScroll()>0?1:-1);

    if(topPanelRenderInfo.zoom <= 1)
        topPanelRenderInfo.zoom = 1;
    if(bottomPanelRenderInfo.zoom <= 1)
        bottomPanelRenderInfo.zoom = 1;
}

void UI_renderUI()
{
    UI_renderTracks(0, UI_middleBar-MIDDLE_BAR_SIZE, topPanelRenderInfo);
    UI_renderTracks(UI_middleBar+MIDDLE_BAR_SIZE, DISPLAY_getDisplayHeight(), bottomPanelRenderInfo);
    RENDER_setColorf(0.7f, 0.7f, 0.7f, 1);
    RENDER_fillRect(0, UI_middleBar-MIDDLE_BAR_SIZE, DISPLAY_getDisplayWidth(), UI_middleBar+MIDDLE_BAR_SIZE);
}

void UI_renderTracks(int y, int y2, TracksRendererInfo info)
{
    RENDER_setColorf(0.4f, 0.4f, 0.4f, 1);
    RENDER_fillRect(0, y, TRACK_INFO_BAR_SIZE, y2);
    glPushMatrix();
    glTranslatef(TRACK_INFO_BAR_SIZE-KEY_COLOR_WIDTH, y+info.panY * info.zoom, 0);
    for(int i = 0; i < trackArray.amount; i++)
    {
        glPushMatrix();
        glTranslatef(0, i*NOTE_AMOUNT*info.zoom, 0);
        RENDER_setColor(trackArray.tracks[i].color);
        RENDER_fillRect(-TRACK_INFO_BAR_SIZE+KEY_COLOR_WIDTH, 3, KEY_COLOR_WIDTH, NOTE_AMOUNT*info.zoom-3);
        for(int j = MAX_NOTE; j >= MIN_NOTE; j--)
        {
            if(j==A_NOTE)
                continue;
            if(isNoteBlack(j))
                RENDER_setColorf(0, 0, 0, 1);
            else
                RENDER_setColorf(1, 1, 1, 1);

            RENDER_fillRect(0, (NOTE_AMOUNT-(j-MIN_NOTE))*info.zoom, KEY_COLOR_WIDTH, (NOTE_AMOUNT-(j-MIN_NOTE+1))*info.zoom);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
