#ifndef KEY_MOU_H
#define KEY_MOU_H

#include "var.h"
#include "func.h"

//funkcije vezane za tastaturu i mis

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

#endif 