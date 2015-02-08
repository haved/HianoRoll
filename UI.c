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

    if(INPUT_isRightMouseDown())
        UI_handlePan();

    if((topPanelRenderInfo.panY*topPanelRenderInfo.zoom) > UI_middleBar-MIDDLE_BAR_SIZE-10)
        topPanelRenderInfo.panY = (UI_middleBar-MIDDLE_BAR_SIZE-10)/topPanelRenderInfo.zoom;

    if(((topPanelRenderInfo.panY+trackArray.amount*NOTE_AMOUNT)*topPanelRenderInfo.zoom) < 10)
        topPanelRenderInfo.panY = 10/topPanelRenderInfo.zoom - trackArray.amount*NOTE_AMOUNT;

    if((bottomPanelRenderInfo.panY*bottomPanelRenderInfo.zoom) > DISPLAY_getDisplayHeight()-10)
        topPanelRenderInfo.panY = (DISPLAY_getDisplayHeight()-10)/bottomPanelRenderInfo.zoom;

    if(((topPanelRenderInfo.panY+trackArray.amount*NOTE_AMOUNT)*topPanelRenderInfo.zoom) < 10)
        topPanelRenderInfo.panY = 10/topPanelRenderInfo.zoom - trackArray.amount*NOTE_AMOUNT;
}

bool m_middleBarHeld;
void UI_updateMiddleBar()
{
    if(INPUT_isLeftMouseDown())
    {
        if(m_middleBarHeld)
        {
            UI_middleBar = INPUT_getMouseY();
        }
        else if(!INPUT_wasLeftMouseDown() & (INPUT_getMouseY() >= (UI_middleBar-MIDDLE_BAR_SIZE)) & (INPUT_getMouseY() <= (UI_middleBar+MIDDLE_BAR_SIZE)))
        {
            m_middleBarHeld = true;
        }
    }
    else
        m_middleBarHeld = false;

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

int m_prevTickX;
int m_prevTickY;
void UI_handlePan()
{
    if(INPUT_wasRightMouseDown())
    {
        if(INPUT_getMouseY()<UI_middleBar-MIDDLE_BAR_SIZE)
            topPanelRenderInfo.panY += (INPUT_getMouseY() - m_prevTickY)/topPanelRenderInfo.zoom;
        else if(INPUT_getMouseY()>UI_middleBar+MIDDLE_BAR_SIZE)
            bottomPanelRenderInfo.panY += (INPUT_getMouseY() - m_prevTickY)/bottomPanelRenderInfo.zoom;
    }

    m_prevTickX = INPUT_getMouseX();
    m_prevTickY = INPUT_getMouseY();
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
    glTranslatef(TRACK_INFO_BAR_SIZE, y+info.panY * info.zoom, 0);
    for(int i = 0; i < trackArray.amount; i++)
    {
        glPushMatrix();
        glTranslatef(0, i*(NOTE_AMOUNT+1)*info.zoom, 0);
        RENDER_setColor(trackArray.tracks[i].color);
        RENDER_fillRect(-TRACK_INFO_BAR_SIZE, 0, 0, (NOTE_AMOUNT)*info.zoom);
        for(int j = MAX_NOTE; j >= MIN_NOTE; j--)
        {
            if(j==A_NOTE)
                continue;
            if(isNoteBlack(j))
                RENDER_setColorf(0, 0, 0, 1);
            else
                RENDER_setColorf(1, 1, 1, 1);

            RENDER_fillRect(-KEY_COLOR_WIDTH, (NOTE_AMOUNT-(j-MIN_NOTE))*info.zoom, 0, (NOTE_AMOUNT-(j-MIN_NOTE+1))*info.zoom);

            if(j%2==0)
                RENDER_setColorf(0.5f, 0.5f, 0.5f, 1);
            else
                RENDER_setColorf(0.3f, 0.3f, 0.3f, 1);

            RENDER_fillRect(0, (NOTE_AMOUNT-(j-MIN_NOTE))*info.zoom, DISPLAY_getDisplayWidth()-TRACK_INFO_BAR_SIZE, (NOTE_AMOUNT-(j-MIN_NOTE+1))*info.zoom);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
