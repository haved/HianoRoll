#include "includes.h"

#define MIDDLE_BAR_SIZE 6

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
    if(UI_middleBar > DISPLAY_getDisplayHeight()-MIDDLE_BAR_SIZE)
        UI_middleBar = DISPLAY_getDisplayHeight()-MIDDLE_BAR_SIZE;

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
}

void UI_renderUI()
{
    RENDER_setColor(0.7f, 0.7f, 0.7f, 1);
    RENDER_fillRect(0, UI_middleBar-MIDDLE_BAR_SIZE, DISPLAY_getDisplayWidth(), UI_middleBar+MIDDLE_BAR_SIZE);
}
