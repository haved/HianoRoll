#include "includes.h"

#define MIDDLE_BAR_SIZE 6
#define TRACK_INFO_BAR_SIZE 180

int UI_middleBar;

void UI_init()
{
    UI_middleBar = DISPLAY_getDisplayHeight() / 2;
}

void UI_updateUI()
{
    UI_updateMiddleBar();
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

void UI_renderUI()
{
    UI_renderTracks(0, UI_middleBar-MIDDLE_BAR_SIZE);
    UI_renderTracks(UI_middleBar+MIDDLE_BAR_SIZE, DISPLAY_getDisplayHeight());
    RENDER_setColor(0.7f, 0.7f, 0.7f, 1);
    RENDER_fillRect(0, UI_middleBar-MIDDLE_BAR_SIZE, DISPLAY_getDisplayWidth(), UI_middleBar+MIDDLE_BAR_SIZE);
}

void UI_renderTracks(int y, int y2)
{
    RENDER_setColor(0.4f, 0.4f, 0.4f, 1);
    RENDER_fillRect(0, y, TRACK_INFO_BAR_SIZE, y2);
}
