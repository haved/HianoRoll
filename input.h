#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

void INPUT_update();
void INPUT_setMouseScroll(int verticalScroll);
int INPUT_getMouseX();
int INPUT_getMouseY();
bool INPUT_isLeftMouseDown();
bool INPUT_isRightMouseDown();
bool INPUT_wasLeftMouseDown();
bool INPUT_wasRightMouseDown();
int INPUT_getMouseScroll();

#endif // INPUT_H_INCLUDED
