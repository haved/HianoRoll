#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

void INPUT_update();
void INPUT_setMouseScroll(int verticalScroll);
int INPUT_getMouseX();
int INPUT_getMouseY();
bool INPUT_isMouseDown();
int INPUT_getMouseScroll();

#endif // INPUT_H_INCLUDED
